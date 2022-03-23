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

	template<typename Item_T, size_t k_max_item_count>
	class Pipe
	{
	public:

		using Item_t = Item_T;

		Pipe() noexcept
			: _begin_idx{ 0 }
			, _end_idx{ 0 }
		{
		}

		~Pipe() noexcept
		{
		}

		Pipe(const Pipe&) = delete;
		Pipe(Pipe&&) = delete;

		Pipe& operator=(const Pipe&) = delete;
		Pipe& operator=(Pipe&&) = delete;

		void push(Item_t item)
		{
			if (!try_push(std::move(item))) {
				throw PipeFull{ "Failed to push into pipe: pipe full" };
			}
		}

		[[nodiscard]] bool try_push(Item_t item)
		{
			if (is_full()) {
				return false;
			}

			gsl::at(_items, _wrapped_index(_end_idx++)) = std::move(item);

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
			return _begin_idx == _end_idx;
		}

		[[nodiscard]] bool is_full() const noexcept
		{
			return _end_idx - _begin_idx == gsl::narrow_cast<gsl::index>(_items.size());
		}

	private:

		[[nodiscard]] gsl::index _wrapped_index(gsl::index idx) const noexcept
		{
			return gsl::narrow_cast<gsl::index>(idx % _items.size());
		}

		using ItemContainer_t = std::array<std::optional<Item_t>, k_max_item_count>;

		ItemContainer_t _items;
		gsl::index _begin_idx;
		gsl::index _end_idx;
	};

}
