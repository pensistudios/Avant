#ifndef _OBJECTIVE_
#define _OBJECTIVE_

#include "prop.h"

namespace Avant
{
	class Objective : public Prop
	{
	public:
		Objective() { comp = false; }
		bool completed() { return comp; }
		void complete() {  comp = true; }
	private:
		bool comp;
	};
};

#endif