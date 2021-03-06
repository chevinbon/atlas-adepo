acquisifier: 
config: 
	 cycle_period_seconds 0 
end. 

default: 
name: BCAM_Default 
instrument: BCAM 
default_post_processing: { 
if {![LWDAQ_is_error_result $result]} { 
append config(run_result) "[lrange $result 1 2]" ; 
 } { 
append config(run_result) " -1 -1 " ; # append joue le meme role que 'set' 
 } 
  set f [open $config(run_results) a] 
 puts $f $result 
 close $f 
 LWDAQ_print $info(text) "Appended modified result to [file tail $config(run_results)]." blue ;  
 set fn [file join [file dirname $config(run_results)] $name.gif] 
 LWDAQ_write_image_file $iconfig(memory_name) $fn 
 LWDAQ_print $info(text) "Saved raw image to $fn" blue ; 
 } 

config: 
	 image_source daq 
	 analysis_enable 1 
	 daq_flash_seconds 0.0000033 
	 daq_adjust_flash 1 
	 daq_ip_addr 10.145.44.16:4090
	 daq_source_ip_addr * 
	 ambient_exposure_seconds 0 
	 intensify exact 
end. 

acquire: 
name: 20MABNDB000069_PR031_PR033
instrument: BCAM 
result: None 
time: 0 
config: 
	 analysis_num_spots 4 
	 daq_driver_socket 4
	 daq_mux_socket 5
	 daq_source_driver_socket 4
	 daq_source_mux_socket 5
	 daq_device_element 2
	 daq_source_device_element "3 4" 
	 daq_image_left 20 
	 daq_image_top 1 
	 daq_image_right 343 
	 daq_image_bottom 243 
end. 

acquire: 
name: 20MABNDB000131_PR032_PR034
instrument: BCAM 
result: None 
time: 0 
config: 
	 analysis_num_spots 4 
	 daq_driver_socket 4
	 daq_mux_socket 6
	 daq_source_driver_socket 4
	 daq_source_mux_socket 6
	 daq_device_element 2
	 daq_source_device_element "3 4" 
	 daq_image_left 20 
	 daq_image_top 1 
	 daq_image_right 343 
	 daq_image_bottom 243 
end. 

acquire: 
name: 20MABNDA000208_PR042_PR046
instrument: BCAM 
result: None 
time: 0 
config: 
	 analysis_num_spots 4 
	 daq_driver_socket 3
	 daq_mux_socket 5
	 daq_source_driver_socket 3
	 daq_source_mux_socket 5
	 daq_device_element 2
	 daq_source_device_element "3 4" 
	 daq_image_left 20 
	 daq_image_top 1 
	 daq_image_right 343 
	 daq_image_bottom 243 
end. 

acquire: 
name: 20MABNDA000035_PR044_PR047
instrument: BCAM 
result: None 
time: 0 
config: 
	 analysis_num_spots 4 
	 daq_driver_socket 3
	 daq_mux_socket 6
	 daq_source_driver_socket 3
	 daq_source_mux_socket 6
	 daq_device_element 2
	 daq_source_device_element "3 4" 
	 daq_image_left 20 
	 daq_image_top 1 
	 daq_image_right 343 
	 daq_image_bottom 243 
end. 

