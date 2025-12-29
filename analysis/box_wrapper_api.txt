# box_wrapper.cpython-39.so - Python API

## Classes

### MultiColorMeterialBoxWrapper
Main Klipper interface for multi-color material box

Methods:
- __init__(config)
- get_status()
- find_objs()
- get_connect_state()
- has_flushing_sign()
- heart_process()
- generate_Tn_func() / generate_Tnn_func()
- get_flush_len() / get_flush_length_from_gcode()
- material_change_flush() / flush_material()
- Tn_action()
- error_clear() / error_resume_process()

G-Code Commands:
- cmd_blow
- cmd_box_enable_CFS_print
- cmd_box_end / cmd_box_end_print
- cmd_box_extrude_material / cmd_box_retrude_material
- cmd_BOX_SET_CURRENT_BOX_IDLE_MODE
- cmd_box_start_print
- cmd_check_material_refill
- cmd_communication_test
- cmd_create_connect
- cmd_ctrl_connection_motor_action
- cmd_cut_material / cmd_cut_state
- cmd_disable_heart_process / cmd_enable_heart_process
- cmd_error_clear / cmd_error_resume_process
- cmd_extrude_process / cmd_extrude2_process
- cmd_extruder_extrude
- cmd_extrusion_all_materials
- cmd_first_power_on_preload
- cmd_generate_flush_array
- cmd_get_box_state / cmd_get_buffer_state
- cmd_get_filament_sensor_state
- cmd_get_flush_len / cmd_get_flush_velocity_test
- cmd_get_gcode_used_tnn
- cmd_get_hardware_status
- cmd_get_remain_len / cmd_get_rfid
- cmd_get_version_sn
- cmd_go_to_extrude_pos
- cmd_hall_test / cmd_hall_zero
- cmd_make_error / cmd_show_error
- cmd_material_change_flush / cmd_material_flush
- cmd_measuring_wheel
- cmd_modify_Tn_data / cmd_modify_Tn_inner_data / cmd_modify_Tnn_map
- cmd_move_to_cut / cmd_move_to_safe_pos
- cmd_nozzle_clean
- cmd_power_loss_restore
- cmd_restore_fan / cmd_save_fan
- cmd_retrude_material_with_tnn / cmd_retrude_process
- cmd_send_data
- cmd_set_box_mode / cmd_set_enable_auto_refill
- cmd_set_pre_loading / cmd_set_temp
- cmd_show_flush_list / cmd_show_Tnn_data
- cmd_tighten_up_enable
- cmd_Tn_Extrude
- cmd_Tnn_retry_process
- cmd_update_same_material_list

### BoxAction
Material handling operations

Methods:
- __init__
- blow()
- box_extrude_material() / box_extrude_material_part() / box_extrude_material_stage8()
- box_retrude_material() / box_retrude_material_filament_err_part()
- cal_flush_list()
- check_and_extrude() / check_flush_temp_and_extrude() / check_speed_and_extrude()
- check_connect() / check_same_box()
- check_material_refill() / check_printing_used_material()
- check_rfid_valid()
- communication_* (multiple RS-485 commands)
- convert_scv() / convert_tcv()
- cut_* (cut operations)
- disable_filament_sensor() / enable_filament_sensor()
- disable_heart_process() / enable_heart_process()
- extrude_process_* / extruder_extrude()
- extrusion_all_materials()
- filament_conflict_check() / filament_err_tighten_up_event()
- find_objs()
- generate_auto_get_rfid_func()
- get_* (various getters)
- go_to_extrude_pos()
- _handle_ready() / _handle_shutdown()
- has_flushing_sign() / set_flushing_sign() / reset_flushing_sign()
- is_material_available() / is_use_ending_material_flush()
- make_material_loose()
- material_auto_refill() / material_flush() / material_volume_to_length()
- motor_send_data()
- move_to_cut() / move_to_safe_pos()
- nozzle_clean()
- power_loss_clean() / power_loss_restore()
- process_msg()
- quickly_wait_heating()
- ret_parse_process()
- retrude_process_clear_flag()
- rfid_check()
- send_data()
- set_cool_temp() / set_temp()
- timeout_process()
- Tn_Extrude()
- update_* (state updates)
- z_down() / z_move() / z_restore()

### BoxState
State management

Methods:
- __init__
- clear_e_err() / e_err_set()
- generate_Tn_data() / generate_Tn_inner_data() / generate_Tn_map()
- generate_Tnn_content() / generate_Tnn_map() / generate_tn_save_data()
- get_* (various getters)
- modify_* (various modifiers)
- state_init()
- sync_tn_data()
- update_same_material_list() / update_tn_save_data()

### BoxSave
Persistence layer

Methods:
- __init__
- clear_err() / get_err() / recode_err()
- clear_resume_tnn() / save_resume_tnn()
- find_objs()
- restore_fan() / save_fan()
- restore_printer_accel() / save_printer_accel()
- save_err_tnn()

### ParseData
Protocol parsing

Methods:
- get_cmd_num()
- get_key_from_value()
- get_measuring_wheel()
- get_remain_len()
- get_rfid()
- parse_num_string_to_byte() / parse_num_to_byte()

### CutSensor
Filament cut sensor

Methods:
- __init__
- _button_handler()
- state()
