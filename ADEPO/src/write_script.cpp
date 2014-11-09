#include "atlas_bcam.h"

//fonction qui permet de generer un script d'acquisition                                            [---> ok
int ATLAS_BCAM::write_script_file(QString fileName, std::vector<BCAM> &bcams)
{
    std::string ipAddress = m_bdd.getDriverIpAddress();

    //écriture dans un fichier
    std::ofstream file(fileName.toStdString().c_str(), std::ios::out | std::ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    if(file)
    {
        std::cerr << "Writing to " << fileName.toStdString() << std::endl;

        //écriture la partie du script qui gère l'enregistrement dans un fichier externe
        file<<"acquisifier: \n"
           <<"config: \n"
           <<"\t cycle_period_seconds 0 \n"
           <<"end. \n"
           <<"\n"
           <<"default: \n"
           <<"name: BCAM_Default \n"
           <<"instrument: BCAM \n"
           <<"default_post_processing: { \n"
           <<"if {![LWDAQ_is_error_result $result]} { \n"
           <<"append config(run_result) \"[lrange $result 1 2]\" ; \n"
           <<" } { \n"
           <<"append config(run_result) \" -1 -1 \" ; # append joue le meme role que 'set' \n"
           <<" } \n"
           <<"  set f [open $config(run_results) a] \n"
           <<" puts $f $result \n"
           <<" close $f \n"
           <<" LWDAQ_print $info(text) \"Appended modified result to [file tail $config(run_results)].\" blue ;  \n"
           <<" set fn [file join [file dirname $config(run_results)] $name.gif] \n"
           <<" LWDAQ_write_image_file $iconfig(memory_name) $fn \n"
           <<" LWDAQ_print $info(text) \"Saved raw image to $fn\" blue ; \n"
           <<" } \n"
           <<"\n"
           <<"config: \n"
           <<"\t image_source daq \n"
           <<"\t analysis_enable 1 \n"
           <<"\t daq_flash_seconds 0.0000033 \n"
           <<"\t daq_adjust_flash 1 \n"
           <<"\t daq_ip_addr "<< ipAddress <<"\n"
           <<"\t daq_source_ip_addr * \n"
           <<"\t ambient_exposure_seconds 0 \n"
           <<"\t intensify exact \n"
           <<"end. \n"
           <<"\n";

        //écriture dans le fichier de la partie acquisition du script : un paragraphe par BCAM
        for(unsigned int i=0; i<bcams.size(); i++)
        {
            std::string name = bcams.at(i).getName().append("_").append(bcams.at(i).getPrism().getName());
            int driverSocket = bcams.at(i).getDriverSocket();
            int muxSocket = bcams.at(i).getMuxSocket();
            int sourceDriverSocket = driverSocket;
            int sourceMuxSocket = muxSocket;

            Prism prism = bcams.at(i).getPrism();
            int deviceElement = prism.getNumChip();
            int left = prism.getLeft();
            int right = prism.getRight();
            int top = prism.getTop();
            int bottom = prism.getBottom();

            int spots;
            std::string sourceDeviceElement;

            if (prism.isPrism()) {
                spots = 2;
                sourceDeviceElement = prism.getNumChip() == 2 ? "3 4" : "1 2";
            } else {
                spots = 2;
                BCAMConfig* bcamConfig = m_bdd.getBCAMConfig(bcams.at(i).getPrism().getName());
                sourceDriverSocket = bcamConfig->getDriverSocket();
                sourceMuxSocket = bcamConfig->getMuxSocket();
                sourceDeviceElement = prism.getNumChip() == 2 ? "1 2" : "3 4";
            }

            file<<"acquire: \n"
                <<"name: "<< name <<"\n"
                <<"instrument: BCAM \n"
                <<"result: None \n"
                <<"time: 0 \n"
                <<"config: \n"
                <<"\n"
                <<"\t analysis_num_spots " << spots << " \n"
                <<"\t daq_driver_socket "<< driverSocket <<"\n"
                <<"\t daq_mux_socket "<< muxSocket <<"\n"
                <<"\t daq_source_mux_socket "<< sourceMuxSocket <<"\n"
                <<"\t daq_source_driver_socket "<< sourceDriverSocket <<"\n"
                <<"\t daq_device_element " << deviceElement << " \n"
                <<"\t daq_source_device_element \"" << sourceDeviceElement << "\" \n"
                <<"\t daq_image_left " << left << " \n"
                <<"\t daq_image_top " << top << " \n"
                <<"\t daq_image_right " << right << " \n"
                <<"\t daq_image_bottom " << bottom << " \n"
                <<"end. \n"
                <<"\n";
        }

        file.close();
        return 1;
    }
    else
    {
        std::cout << "Could not write script" << std::endl;
        return 0;
    }
}

