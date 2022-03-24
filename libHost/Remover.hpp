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

	void execute() override;

private:
	AlarmPipe& _ingress;
	AlarmPipe& _egress;
	const Alarm::Type _to_remove;
};

}
