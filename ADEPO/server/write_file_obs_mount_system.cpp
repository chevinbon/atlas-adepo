#include "write_file_obs_mount_system.h"
#include "changement_repere.h"
#include "Eigen/Eigen"
#include "math.h"
#include "Eigen/Core"
#include "iostream"
#include "iomanip"
#include "ctime"
#include "sstream"
#include <QString>

#define um2m 0.000001

using namespace std;

int write_file_obs_mount_system(QString fileName, QString datetime, BDD &base_donnees, Configuration &config)
{
    //écriture dans un fichier
    std::ofstream fichier(fileName.toStdString().c_str(), std::ios::out | std::ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    if(!fichier)
    {
        std::cout << "WARNING Cannot write output file " << fileName.toStdString() << std::endl;
        return 0;
    }

  // setup default precision
    fichier<<std::fixed<<std::setprecision(8);

    std::cout << "Writing results into " << fileName.toStdString() << std::endl;

    fichier<<"********** Fichier qui contient une sauvegarde des coordonnees images + coordonnees images transformees dans le repere BCAM (MOUNT) + coordonnees des prismes dans le repere MOUNT********** \n"
           <<"********************************************************************** Unite en metres (m)************************************************************************************************** \n"
           <<"\n";

        //premiere visee BCAM-Prisme de la liste des observations
        std::string premier_objet_img= base_donnees.getDualSpots().at(0).getName();

        //sauvegarde des coordonnees images
        fichier<<"*******************************************************************coordonnees images dans le repere CCD *********************************************************************************** \n";
        for(unsigned int i=0; i<base_donnees.getDualSpots().size(); i++)
        {
            DualSpot spot1 = base_donnees.getDualSpots().at(i);
            if(i>0 && spot1.getName() == premier_objet_img) //si on a tout parcourut et on revient au premier objet ==> fin
                break;

            fichier<<spot1.getName()<<"\n";
            for(unsigned int j=0; j<base_donnees.getDualSpots().size(); j++)
            {
                DualSpot spot2 = base_donnees.getDualSpots().at(j);
                if(spot1.getName() == spot2.getName())
                {
                    fichier
                                   <<"Spot 1"<<" "<<setw(14)<<spot2.getSpot1().i()*um2m<<" "<<setw(14)<<spot2.getSpot1().j()*um2m<<"\n"
                                   <<"Spot 2"<<" "<<setw(14)<<spot2.getSpot2().i()*um2m<<" "<<setw(14)<<spot2.getSpot2().j()*um2m<<"\n";
                }
            }
        }

        fichier<<"\n"
               <<"\n"
               <<"****************************************************************coordonnees images transformees dans le repere MOUNT************************************************************************* \n";
        std::string premier_objet_mount = base_donnees.getMountCoordSpots().at(0).getName();

        //sauvegarde des coordonnees images transformees dans le repere MOUNT
        for(unsigned int i=0; i<base_donnees.getMountCoordSpots().size(); i++)
        {
            MountCoordSpots spots1 = base_donnees.getMountCoordSpots().at(i);
//                std::cout << base_donnees.getMountCoordSpots().size() << " " << spots1.getName() << " " << premier_objet_mount << std::endl;
            if(i>0 && spots1.getName() == premier_objet_mount) //si on a tout parcourut et on revient au premier objet ==> fin
                break;

            fichier<<spots1.getName()<<"\n";
            for(unsigned int j=0; j<base_donnees.getMountCoordSpots().size(); j++)
            {
                MountCoordSpots spots2 = base_donnees.getMountCoordSpots().at(j);
                if(spots1.getName() == spots2.getName())
                {
                    fichier<<"Spot 1"<<" "<<setw(14)<<spots2.getCoord1().x()<<" "<<setw(14)<<spots2.getCoord1().y()<<" "<<setw(14)<<spots2.getCoord1().z()<<"\n"
                           <<"Spot 2"<<" "<<setw(14)<<spots2.getCoord2().x()<<" "<<setw(14)<<spots2.getCoord2().y()<<" "<<setw(14)<<spots2.getCoord2().z()<<"\n";
                }
            }
        }

        fichier<<"\n"
               <<"\n"
               <<"*****************************************************************coordonnees du prisme dans le repere MOUNT********************************************************************************** \n";
        //sauvegarde des coordonnees du prisme dans le repere MOUNT pour chaque paire de spots
        std::string premier_prisme_mount = base_donnees.getMountCoordPrisms().at(0).getName();

        for(unsigned int i=0; i<base_donnees.getMountCoordPrisms().size(); i++)
        {
            MountCoordPrism prism1 = base_donnees.getMountCoordPrisms().at(i);
            if(i>0 && prism1.getName() == premier_prisme_mount) //si on a tout parcourut et on revient au premier objet ==> fin
                break;

            fichier<<prism1.getName()<<"\n";
            for(unsigned int j=0; j<base_donnees.getMountCoordPrisms().size(); j++)
            {
                MountCoordPrism prism2 = base_donnees.getMountCoordPrisms().at(j);
                if(prism1.getName() == prism2.getName())
                {
                    fichier<<setw(14)<<prism2.getCoordPrismMountSys().x()<<" "<<setw(14)<<prism2.getCoordPrismMountSys().y()<<" "<<setw(14)<<prism2.getCoordPrismMountSys().z()<<"\n";
                }
            }
        }

        fichier<<"\n"
               <<"\n"
               <<"*****************************************************************coordonnees du prisme dans le repere ATLAS********************************************************************************** \n";
        //sauvegarde des coordonnees du prisme dans le repere ATLAS pour chaque paire de spots
        std::string premier_prisme_atlas = base_donnees.getGlobalCoordPrisms().at(0).getName();

        for(unsigned int i=0; i<base_donnees.getGlobalCoordPrisms().size(); i++)
        {
            GlobalCoordPrism prism1 = base_donnees.getGlobalCoordPrisms().at(i);
            if(i>0 && prism1.getName() == premier_prisme_atlas)
                break;

            fichier<<prism1.getName()<<" "<<prism1.getAirpad()<<"\n";
            for(unsigned int j=0; j<base_donnees.getGlobalCoordPrisms().size(); j++)
            {
                GlobalCoordPrism prism2 = base_donnees.getGlobalCoordPrisms().at(j);
                if(prism1.getName() == prism2.getName())
                {
                    fichier<<setw(14)<<prism2.getCoordPrismMountSys().x()<<" "<<setw(14)<<prism2.getCoordPrismMountSys().y()<<" "<<setw(14)<<prism2.getCoordPrismMountSys().z()<<"\n";
                }
            }
        }
        fichier<<"\n"
               <<"\n"
               <<"*****************************************************************Rapport********************************************************************************** \n";
        //on parcourt tous les points transformes dans le repere global : moyenne + dispersion

        for(unsigned int i=0; i<base_donnees.getGlobalCoordPrisms().size(); i++)
        {
            GlobalCoordPrism prism1 = base_donnees.getGlobalCoordPrisms().at(i);
            if(i>0 && prism1.getName() == premier_prisme_atlas)
                break;

            Eigen::MatrixXd coord(Eigen::DynamicIndex,3);
            int ligne=0;

            for(unsigned int j=0; j<base_donnees.getGlobalCoordPrisms().size(); j++)
            {
                GlobalCoordPrism prism2 = base_donnees.getGlobalCoordPrisms().at(j);
                if(prism1.getName() == prism2.getName())
                {
                    coord(ligne,0)=prism2.getCoordPrismMountSys().x();
                    coord(ligne,1)=prism2.getCoordPrismMountSys().y();
                    coord(ligne,2)=prism2.getCoordPrismMountSys().z();
                    ligne=ligne+1;
                }
            }
            Eigen::MatrixXd result_mean(1,3); //resultat de la moyenne
            result_mean=coord.colwise().sum()/ligne; //somme de chaque colonne / par le nombre de lignes

            Eigen::MatrixXd result_var(ligne,3); //calcul de la variance
            for(int k=0; k<ligne; k++)
            {
                result_var(k,0)=(coord(k,0)-result_mean(0,0))*(coord(k,0)-result_mean(0,0));
                result_var(k,1)=(coord(k,1)-result_mean(0,1))*(coord(k,1)-result_mean(0,1));
                result_var(k,2)=(coord(k,2)-result_mean(0,2))*(coord(k,2)-result_mean(0,2));
            }

            Eigen::MatrixXd result_std_square(1,3); //calcul de l'ecart-type au carre
            result_std_square=result_var.colwise().sum()/ligne;

            Eigen::MatrixXd result_std(1,3);       //calcul de l'ecart-type
            for(int m=0; m<3; m++)
            {
                result_std(0,m) = sqrt(result_std_square(0,m));
            }

            //nomenclature dans le repere ATLAS
            GlobalCoordPrism prism = prism1;
            std::string name_bcam_atlas = config.getName(prism.getBCAM().getName());
            std::string name_prism_atlas = config.getName(prism.getPrism().getName());
            float airpad = prism1.getAirpad();

            //delta selon composantes axiales
            float delta_x=0;
            float delta_y=0;
            float delta_z=0;
            //ajout de la constante de prisme
            for(unsigned int n=0; n<config.getPrismCorrections().size(); n++)
            {
                PrismCorrection correction = config.getPrismCorrections().at(n);
                if(prism1.getPrism().getName() == correction.getPrism())
                {
                    delta_x = correction.getDelta().x();
                    delta_y = correction.getDelta().y();
                    delta_z = correction.getDelta().z();
                }
            }
            //enregistrement dans le fichier de resultats
            std::string name = name_bcam_atlas.append("_").append(name_prism_atlas);
            fichier<<left<<setw(30)<<name<<" "<<datetime.toStdString()<<" "
                 <<right<<setw(14)<<result_mean(0,0)+delta_x<<" "<<setw(14)<<result_mean(0,1)+delta_y<<" "<<setw(14)<<result_mean(0,2)+delta_z<<" "
                 <<setw(14)<<result_std(0,0)<<" "<<setw(14)<<result_std(0,1)<<" "<<setw(14)<<result_std(0,2)
                 <<" "<<airpad<<" VRAI \n";
        }

    fichier.close();
    return 1;
}
