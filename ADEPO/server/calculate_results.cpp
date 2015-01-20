
void ATLAS_BCAM::calculateResults(BDD &base_donnees, std::map<std::string, result> &results) {

    //on parcourt tous les points transformes dans le repere global : moyenne + dispersion
    // current date/time based on current system
    QString now = getDateTime();

    //sauvegarde des coordonnees du prisme dans le repere ATLAS pour chaque paire de spots
    std::string premier_prisme_atlas = base_donnees.getGlobalCoordPrisms().at(0).getName();

    for(unsigned int i=0; i<base_donnees.getGlobalCoordPrisms().size(); i++)
    {
        if(i>0 && base_donnees.getGlobalCoordPrisms().at(i).getName() == premier_prisme_atlas)
            break;

        GlobalCoordPrism prism = base_donnees.getGlobalCoordPrisms().at(i);

        //nomenclature dans le repere ATLAS
        std::string name_prism_atlas = config.getName(prism.getPrism().getName());

        result& result = results[name_prism_atlas];
        result.setName(name_prism_atlas);
        result.setTime(now.toStdString());

        Eigen::MatrixXd coord(Eigen::DynamicIndex,3);
        int ligne=0;

        for(unsigned int j=0; j<base_donnees.getGlobalCoordPrisms().size(); j++)
        {
            GlobalCoordPrism checkedPrism = base_donnees.getGlobalCoordPrisms().at(j);
            if(prism.getName() == checkedPrism.getName())
            {
                coord(ligne,0)=checkedPrism.getCoordPrismMountSys().x();
                coord(ligne,1)=checkedPrism.getCoordPrismMountSys().y();
                coord(ligne,2)=checkedPrism.getCoordPrismMountSys().z();
                ligne=ligne+1;
            }
        }

        result.setN(ligne);

        Eigen::MatrixXd mean(1,3);
        mean = coord.colwise().sum()/ligne; //somme de chaque colonne / par le nombre de lignes

        Eigen::MatrixXd result_var(ligne,3); //calcul de la variance
        for(int k=0; k<ligne; k++)
        {
            result_var(k,0)=(coord(k,0)-mean(0,0))*(coord(k,0)-mean(0,0));
            result_var(k,1)=(coord(k,1)-mean(0,1))*(coord(k,1)-mean(0,1));
            result_var(k,2)=(coord(k,2)-mean(0,2))*(coord(k,2)-mean(0,2));
        }

        Eigen::MatrixXd result_std_square(1,3); //calcul de l'ecart-type au carre
        result_std_square=result_var.colwise().sum()/ligne;

        result.setStd(Point3f(sqrt(result_std_square(0,0)),sqrt(result_std_square(0,1)),sqrt(result_std_square(0,2))));

        //delta selon composantes axiales
        float dx=0;
        float dy=0;
        float dz=0;
        //ajout de la constante de prisme
        for(unsigned int n=0; n<config.getPrismCorrections().size(); n++)
        {
            PrismCorrection correction = config.getPrismCorrections().at(n);
            if(base_donnees.getGlobalCoordPrisms().at(i).getPrism().getName() == correction.getPrism())
            {
                dx = correction.getDelta().x();
                dy = correction.getDelta().y();
                dz = correction.getDelta().z();
            }
        }

        result.setValue(Point3f(mean(0,0) + dx, mean(0,1) + dy, mean(0,2) + dz));

        results[name_prism_atlas] = result;
    }
}