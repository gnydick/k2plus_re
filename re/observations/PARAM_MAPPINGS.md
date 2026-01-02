# Parameter Name Mappings

These parameters need to be renamed in the implementation code:

## box_wrapper

### BoxAction.box_extrude_material_part
- `length` -> `retry`

### BoxAction.cal_flush_list
- `used_tnns` -> `src_length`

### BoxAction.check_and_extrude
- `length` -> `extrude`

### BoxAction.check_flush_temp_and_extrude
- `temp` -> `index`

### BoxAction.check_printing_used_material
- `tnns` -> `addr`

### BoxAction.check_same_box
- `tnn1` -> `tnn`

### BoxAction.check_speed_and_extrude
- `length` -> `extrude`
- `max_speed` -> `velocity`

### BoxAction.communication_ctrl_connection_motor_action
- `action` -> `act`

### BoxAction.communication_extrude2_process
- `slot` -> `num`
- `length` -> `trigger`

### BoxAction.communication_extrude_process
- `slot` -> `num`

### BoxAction.communication_get_remain_len
- `slot` -> `num`

### BoxAction.communication_get_rfid
- `slot` -> `num`

### BoxAction.communication_measuring_wheel
- `slot` -> `action`

### BoxAction.communication_retrude_process
- `slot` -> `num`

### BoxAction.communication_set_box_mode
- `mode` -> `m`

### BoxAction.communication_set_pre_loading
- `slot` -> `action`
- `enable` -> `num`

### BoxAction.communication_test
- `addr` -> `count`

### BoxAction.convert_scv
- `value` -> `cv`

### BoxAction.convert_tcv
- `value` -> `cv`

### BoxAction.extruder_extrude
- `length` -> `tnn`

### BoxAction.generate_auto_get_rfid_func
- `slot` -> `addr`

### BoxAction.get_flush_len
- `from_tnn` -> `scv`
- `to_tnn` -> `tcv`

### BoxAction.get_flush_max_temp
- `from_tnn` -> `last_tnn`
- `to_tnn` -> `current_tnn`

### BoxAction.get_flush_temp
- `from_tnn` -> `last_tnn`
- `to_tnn` -> `current_tnn`

### BoxAction.get_flush_velocity
- `from_tnn` -> `last_tnn`
- `to_tnn` -> `current_tnn`

### BoxAction.material_auto_refill
- `tnn` -> `eventtime`

### BoxAction.material_flush
- `from_tnn` -> `length`
- `to_tnn` -> `velocity`
- `length` -> `temp`

### BoxAction.motor_send_data
- `data` -> `addr`
- `timeout` -> `cmd`

### BoxAction.process_msg
- `response` -> `data_send`

### BoxAction.quickly_wait_heating
- `target_temp` -> `set_temp`

### BoxAction.ret_parse_process
- `response` -> `data_send`
- `expected_func` -> `msg`

### BoxAction.rfid_check
- `slot` -> `rfid`

### BoxAction.send_data
- `data` -> `addr`
- `timeout` -> `cmd`

### BoxAction.update_filament_pos
- `slot` -> `tnn`
- `pos` -> `data`

### BoxAction.update_same_material_list
- `material_list` -> `eventtime`

### BoxAction.update_state_process
- `data` -> `addr`

### BoxAction.update_tn_save_data
- `slot` -> `eventtime`

### BoxSave.recode_err
- `err_info` -> `err`

### BoxSave.save_err_tnn
- `tnn` -> `last_tnn`

### BoxState.get_Tn_data
- `slot` -> `addr`

### BoxState.get_Tn_inner_data
- `slot` -> `addr`

### BoxState.get_Tnn_content
- `tnn_index` -> `tnn`

### BoxState.get_tn_save_data
- `slot` -> `addr`

### BoxState.modify_Tn_data
- `slot` -> `addr`
- `key` -> `data`
- `value` -> `part`

### BoxState.modify_Tn_inner_data
- `slot` -> `addr`
- `key` -> `data`
- `value` -> `part`

### BoxState.modify_tn_save_data
- `slot` -> `addr`

### BoxState.update_tn_save_data
- `slot` -> `part`
- `key` -> `enable`
- `value` -> `tnn_map`

### CutSensor.__init__
- `box_action` -> `switch_pin`

### MultiColorMeterialBoxWrapper.Tn_action
- `tnn` -> `vtnn`

### MultiColorMeterialBoxWrapper.filament_err_retry_process
- `tnn` -> `last_tnn`

### MultiColorMeterialBoxWrapper.flush_material
- `from_tnn` -> `velocity`

### MultiColorMeterialBoxWrapper.generate_Tn_func
- `tnn` -> `tn`

### MultiColorMeterialBoxWrapper.get_flush_len
- `from_tnn` -> `last_tnn`
- `to_tnn` -> `current_tnn`

### MultiColorMeterialBoxWrapper.get_flush_length_from_gcode
- `gcode_file` -> `last_tnn`

### MultiColorMeterialBoxWrapper.get_status
- `eventtime` -> `eventime`

### MultiColorMeterialBoxWrapper.material_change_flush
- `from_tnn` -> `last_tnn`
- `to_tnn` -> `tnn`

### ParseData.get_cmd_num
- `data` -> `data_send`

### ParseData.get_key_from_value
- `mapping` -> `dict`
- `value` -> `v`

### ParseData.get_measuring_wheel
- `data` -> `data_send`

### ParseData.get_remain_len
- `data` -> `data_send`

### ParseData.get_rfid
- `data` -> `msg`

### ParseData.parse_num_string_to_byte
- `num_str` -> `data`

### ParseData.parse_num_to_byte
- `num` -> `data`

## filament_rack_wrapper

### FilamentRackWrapper.get_material_target_speed
- `rfid` -> `type`

### FilamentRackWrapper.get_material_target_temp
- `rfid` -> `type`

### FilamentRackWrapper.quickly_wait_heating
- `target_temp` -> `set_temp`

### FilamentRackWrapper.send_data
- `data` -> `eventtime`

## motor_control_wrapper

### Motor_Control.bytes_to_int
- `data` -> `bytes_obj`
- `signed` -> `is_data_obj`

### Motor_Control.check_and_retry
- `func` -> `num`

### Motor_Control.check_protection_code
- `axis` -> `cur_obj`

### Motor_Control.data_pack
- `motor_num` -> `addr`
- `data_list` -> `data`

### Motor_Control.data_pack_extruder
- `cmd` -> `addr`
- `data_list` -> `cmd`

### Motor_Control.get_status
- `eventtime` -> `eventime`

### Motor_Control.motor_extruder_control
- `enable` -> `gcmd`

### Motor_Control.motor_extruder_get
- `param` -> `gcmd`

### Motor_Control.motor_extruder_set485_addr
- `addr` -> `gcmd`

### Motor_Control.set_motor_pin_dir
- `motor` -> `toolhead`

### Motor_Control.set_motor_pin_normal
- `motor` -> `toolhead`

### Motor_Control.validate_param
- `param` -> `gcmd`

## prtouch_v1_wrapper

### PRTouchEndstopWrapper.bed_mesh_post_proc
- `mesh_data` -> `last_point`

### PRTouchEndstopWrapper.cal_tri_data
- `data` -> `start_step`

### PRTouchEndstopWrapper.check_bed_mesh
- `mesh_data` -> `auto_g29`

### PRTouchEndstopWrapper.ck_and_raise_error
- `error_code` -> `ck`

### PRTouchEndstopWrapper.delay_s
- `seconds` -> `delay_s`

### PRTouchEndstopWrapper.get_best_rdy_z
- `positions` -> `rdy_x`

### PRTouchEndstopWrapper.get_linear2
- `x1` -> `p1`
- `y1` -> `p2`
- `x2` -> `po`
- `y2` -> `is_base_x`

### PRTouchEndstopWrapper.print_ary
- `array` -> `title`

### PRTouchEndstopWrapper.print_msg
- `msg` -> `title`

### PRTouchEndstopWrapper.print_res
- `result` -> `title`

### PRTouchEndstopWrapper.run_re_g29s
- `positions` -> `last_point`

### PRTouchEndstopWrapper.run_step_prtouch
- `run_dis` -> `down_min_z`
- `run_spd` -> `probe_min_3err`
- `direction` -> `rt_last`
- `send_ms` -> `pro_cnt`
- `acc_ctl_cnt` -> `crt_cnt`
- `low_spd_nul` -> `fast_probe`
- `send_step_duty` -> `re_g28`

### PRTouchEndstopWrapper.run_to_next
- `x` -> `nextpos`
- `y` -> `wait`

### PRTouchEndstopWrapper.safe_move_z
- `z` -> `run_sta`
- `speed` -> `run_dis`

### PRTouchEndstopWrapper.send_wave_tri
- `data` -> `ch`

### PRTouchEndstopWrapper.set_fan_speed
- `speed` -> `fan_name`

## prtouch_v2_wrapper

### PRTouchEndstopWrapper.bed_mesh_post_proc
- `mesh_data` -> `last_point`

### PRTouchEndstopWrapper.cal_tri_data
- `data` -> `start_step`

### PRTouchEndstopWrapper.check_bed_mesh
- `mesh_data` -> `auto_g29`

### PRTouchEndstopWrapper.ck_and_raise_error
- `error_code` -> `ck`

### PRTouchEndstopWrapper.delay_s
- `seconds` -> `delay_s`

### PRTouchEndstopWrapper.get_best_rdy_z
- `positions` -> `rdy_x`

### PRTouchEndstopWrapper.get_linear2
- `x1` -> `p1`
- `y1` -> `p2`
- `x2` -> `po`
- `y2` -> `is_base_x`

### PRTouchEndstopWrapper.run_step_prtouch
- `run_dis` -> `down_min_z`
- `run_spd` -> `probe_min_3err`
- `direction` -> `rt_last`
- `send_ms` -> `pro_cnt`
- `acc_ctl_cnt` -> `crt_cnt`
- `low_spd_nul` -> `fast_probe`
- `send_step_duty` -> `re_g28`

### PRTouchEndstopWrapper.safe_move_z
- `z` -> `run_sta`
- `speed` -> `run_dis`

## prtouch_v3_wrapper

### PRTouchEndstopWrapper.calc_z
- `trigger_time` -> `x`
- `trigger_pos` -> `y`

### PRTouchEndstopWrapper.check_reise
- `z_pos` -> `ck`

### PRTouchEndstopWrapper.delay_s
- `seconds` -> `delay_s`

### PRTouchEndstopWrapper.disturb_ctl
- `enable` -> `is_set`

### PRTouchEndstopWrapper.gcode_move
- `x` -> `pos`
- `y` -> `speed`
- `z` -> `wait`
- `speed` -> `showlog`

### PRTouchEndstopWrapper.get_temp_compensate
- `z_pos` -> `noz_temp`

### PRTouchEndstopWrapper.get_temperature_compensate
- `z_pos` -> `noz_temp`

### PRTouchEndstopWrapper.print_msg
- `msg` -> `title`

### PRTouchEndstopWrapper.probe_outlier_check
- `positions` -> `src_matx`

### PRTouchEndstopWrapper.run_script_from_command
- `script` -> `cmd_line`

