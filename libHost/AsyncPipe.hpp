#pragma once

#include "Pipe.hpp"

#include <mutex>

namespace kjc
{
	template<typename Item_T, size_t k_max_item_count>
	class AsyncPipe : PipeBase<Item_T, std::atomic<gsl::index>, k_max_item_count>
	{
		using PipeBase_t = PipeBase<Item_T, std::atomic<gsl::index>, k_max_item_count>;
		using Mutex_t = std::mutex;
		using Lock_t = std::lock_guard<Mutex_t>;

	public:
		using Item_t = Item_T;
		using Callback_t = std::function<void()>;

		AsyncPipe() noexcept = default;
		~AsyncPipe() noexcept = default;

		AsyncPipe(const AsyncPipe&) = delete;
		AsyncPipe(AsyncPipe&&) = delete;

		AsyncPipe& operator=(const AsyncPipe&) = delete;
		AsyncPipe& operator=(AsyncPipe&&) = delete;

		void set_item_arrived_callback(Callback_t cb)
		{
			Lock_t lock(_mutex);
			_notify_item_arrived = std::move(cb);
		}

		template< typename T>
		void push(T&& item)
		{
			Lock_t lock(_mutex);
			PipeBase_t::push(std::forward<T>(item);
			if (_notify_item_arrived) {
				std::invoke(_notify_item_arrived);
			}
		}

		template<typename T>
		[[nodiscard]] bool try_push(T&& item)
		{
			Lock_t lock(_mutex);
			if (PipeBase_t::try_push(std::forward<T>(item))) {
				if (_notify_item_arrived) {
					std::invoke(_notify_item_arrived);
				}

				return true;
			}

			return false;
		}

		[[nodiscard]] Item_t pull()
		{
			Lock_t lock(_mutex);
			return PipeBase_t::pull();
		}

		[[nodiscard]] std::optional<Item_t> try_pull()
		{
			Lock_t lock(_mutex);
			return PipeBase_t::try_pull();
		}

		using PipeBase_t::count;
		using PipeBase_t::is_empty;
		using PipeBase_t::is_full;

	private:
		Mutex_t _mutex;
		Callback_t _notify_item_arrived{ nullptr };
	};
}
