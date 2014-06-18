#include "header/mount_prism_to_global_prism.h"
#include "header/changement_repere.h"

void mount_prism_to_global_prism(bdd & base_donnees)
{
    std::cout << "y" << std::endl;
    for(unsigned int i=0; i<base_donnees.Get_liste_mount_coord_prism().size(); i++)
    {
        std::cout << "x" << std::endl;
        for(unsigned int j=0; j<base_donnees.Get_liste_BCAM_params().size(); j++)
        {
            std::cout << "=" << std::endl;
            if(base_donnees.Get_liste_mount_coord_prism().at(i).Get_id().substr(0,14) == base_donnees.Get_liste_BCAM_params().at(j).Get_id_bcam())
            {
                 std::cout << "+" << std::endl;
                 Point3f point_transforme = changement_repere(base_donnees.Get_liste_mount_coord_prism().at(i).Get_coord_prism_mount_sys(), base_donnees.Get_liste_BCAM_params().at(j).Get_translation(), base_donnees.Get_liste_BCAM_params().at(j).Get_rotation());
                 mount_coord_prism pt_global(base_donnees.Get_liste_mount_coord_prism().at(i).Get_id(), point_transforme);
                 base_donnees.Add_global_coord_prism(pt_global);
            }
        }
    }

    //affichage base de donnee des prismes dans le repere global
    /*for(int k=0; k<base_donnees.Get_liste_global_coord_prism().size(); k++)
    {
        base_donnees.Get_liste_global_coord_prism().at(k).Affiche();
    }*/
}
