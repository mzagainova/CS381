/*
 * UnitAI.h
 *
 *  Created on: Mar 31, 2018
 *      Author: mzagainova
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <Aspect.h>

class UnitAI : public Aspect {
public:
	UnitAI();
	virtual ~UnitAI();

	void Tick(float dt);

	void SetCommand(Command *c);
	void AddCommand(Command *c);

	Entity381* ent;
	std::list<Command*> commands;
};



#endif /* INC_UNITAI_H_ */
