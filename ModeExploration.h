#ifndef MODEEXPLORATION_H
#define MODEEXPLORATION_H

#include "Servomoteurs.h"
#include "Moteurs.h"
#include <PID_v1.h>
#include "JY901.h"
#include "FonctionsDeBaseMoteur.h"

class ModeExploration
{
    public:
        ModeExploration();
        virtual ~ModeExploration();

        void ArretUrg();
        void Explo1();

    protected:

    private:
        FonctionsDeBaseMoteur Fonctions;
};

#endif // MODEEXPLORATION_H
