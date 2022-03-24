#pragma once

#include "Filter.hpp"
#include "Alarm.hpp"

namespace kjc
{

class AlarmPipe;

class Remover : public Filter
{
public :
	Remover(AlarmPipe& ingress, AlarmPipe& egress, Alarm::Type to_remove) noexcept;

	Remover(const Remover&) = delete;
	Remover(Remover&&) = delete;
	Remover& operator=(const Remover&) = delete;
	Remover& operator=(Remover&&) = delete;

	void execute() override;

private:
	const Alarm::Type _to_remove;

	AlarmPipe& _ingress;
	AlarmPipe& _egress;
};

}
