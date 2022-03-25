#pragma once

#include <gsl/gsl>

#include <stdexcept>
#include <string>
#include <optional>
#include <array>

namespace kjc
{
	class PipeException : public std::runtime_error
	{
	public:
		explicit PipeException(std::string_view msg) : std::runtime_error{ msg.data() } {}
	};

	class PipeFull : public PipeException
	{
	public:
		explicit PipeFull(std::string_view msg) : PipeException{ msg } {}
	};

	class PipeEmpty : public PipeException
	{
	public:
		explicit PipeEmpty(std::string_view msg) : PipeException{ msg } {}
	};

	template<typename Item_T, typename Index_T, size_t k_max_item_count>
	class PipeBase
	{
	public:
		using Index_t = Index_T;
		using Item_t = Item_T;

		PipeBase() noexcept
			: _begin_idx{ 0 }
			, _end_idx{ 0 }
		{
		}

		~PipeBase() noexcept
		{
		}

		PipeBase(const PipeBase&) = delete;
		PipeBase(PipeBase&&) = delete;

		PipeBase& operator=(const PipeBase&) = delete;
		PipeBase& operator=(PipeBase&&) = delete;

		template< typename T>
		void push(T&& item)
		{
			if (!try_push(std::forward<T>(item))) {
				throw PipeFull{ "Failed to push into pipe: pipe full" };
			}
		}

		template<typename T>
		[[nodiscard]] bool try_push(T&& item)
		{
			if (is_full()) {
				return false;
			}

			gsl::at(_items, _wrapped_index(_end_idx++)) = std::make_optional<Item_t>(std::forward<T>(item));

			return true;
		}

		[[nodiscard]] Item_t pull()
		{
			auto item = try_pull();
			if (!item) {
				throw PipeEmpty{ "Failed to pull item from pipe: pipe empty" };
			}

			return std::move(*item);
		}

		[[nodiscard]] std::optional<Item_t> try_pull()
		{
			if (is_empty()) {
				return std::nullopt;
			}

			const auto idx = _wrapped_index(_begin_idx);

			auto out = std::move(gsl::at(_items, idx));
			gsl::at(_items, idx) = std::nullopt;
			++_begin_idx;

			return out;
		}

		[[nodiscard]] bool is_empty() const noexcept
		{
			return count() == 0;
		}

		[[nodiscard]] bool is_full() const noexcept
		{
			return count() == gsl::narrow_cast<Index_t>(_items.size());
		}

		[[nodiscard]] size_t count() const noexcept
		{
			return _end_idx - _begin_idx;
		}

	private:

		[[nodiscard]] Index_t _wrapped_index(const Index_t& idx) const noexcept
		{
			return gsl::narrow_cast<Index_t>(idx % _items.size());
		}

		using ItemContainer_t = std::array<std::optional<Item_t>, k_max_item_count>;

		ItemContainer_t _items;
		Index_t _begin_idx;
		Index_t _end_idx;
	};


	template<typename Item_T, size_t k_max_item_count>
	using Pipe = PipeBase<Item_T, gsl::index, k_max_item_count>;
}
