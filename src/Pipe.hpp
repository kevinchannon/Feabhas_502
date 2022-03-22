#pragma once

namespace kjc
{
	class PipeException : public std::runtime_error
	{
	public:
		PipeException(std::string_view msg) : std::runtime_error{ msg.data() } {}
	};

	class PipeFull : public PipeException
	{
	public:
		PipeFull(std::string_view msg) : PipeException{ msg } {}
	};

	class PipeEmpty : public PipeException
	{
	public:
		PipeEmpty(std::string_view msg) : PipeException{ msg } {}
	};

	template<typename Item_T, size_t MAX_ITEM_COUNT>
	class Pipe
	{
	public:

		using Item_t = Item_T;

		Pipe()
			: _begin_idx{0}
			, _end_idx{0}
		{
			spdlog::debug("Pipe default c'tor");
		}

		~Pipe()
		{
			spdlog::debug("Pipe d'tor");
		}

		void push(Item_t item)
		{
			if (!try_push(std::move(item))) {
				throw PipeFull{"Failed to push into pipe: pipe full"};
			}
		}

		bool try_push(Item_t item)
		{
			if (is_full()) {
				return false;
			}

			_items[_end_idx++ % _items.size()] = std::move(item);

			return true;
		}

		Item_t pull()
		{
			auto item = try_pull();
			if (!item) {
				throw PipeEmpty{ "Failed to pull item from pipe: pipe empty" };
			}

			return std::move(*item);
		}

		std::optional<Item_t> try_pull()
		{
			if (is_empty()) {
				return std::nullopt;
			}

			return std::move(_items[_begin_idx++ % _items.size()]);
		}

		bool is_empty() const
		{
			return _begin_idx == _end_idx;
		}

		bool is_full() const
		{
			return _end_idx - _begin_idx == _items.size();
		}

	private:

		using ItemContainer_t = std::array<std::optional<Item_t>, MAX_ITEM_COUNT>;

		ItemContainer_t _items;
		size_t _begin_idx;
		size_t _end_idx;
	};

}
