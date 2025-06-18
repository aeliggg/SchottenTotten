#pragma once
#include "Partie.h"
#include "PartieClassique.h"
#include "PartieClassiquePvP.h"
class PartieClassiquePvP : public PartieClassique {
	public :
		bool jouer() override;
}