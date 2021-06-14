; Flame
; The target whick is marked will take more burning damage.

(define "fire_contact"
	{if not tagged "valid"
		{delay_ex 0
			{if not tagged "in_hole"
				{delete}
			}
		}
	else effector "fire_deleter"
		{if tagged "can_be_removed"
			{delete}
		}
	else effector "fire_fuse"
		{if tagged "can_be_fused"
			{tags add "detonated"}
		}
	else effector "fire_fuse_human"
		{if tagged "detonated"
			{if rand 0.9
				{tags add "contact_human"}
				{call "to_end"}
			}
		else
			{if rand 0.1
				{tags add "contact_human"}
				{call "to_end"}
			}
		}
	else effector "vehicle"
		{tags add "contact_vehicle"}
		{call "to_end"}
	else effector "fence"
		{delay_ex 0
			{if not tagged "in_hole"
				{call "to_end"}
			}
		}
	else effector "small construction parts"
		{delay_ex 0
			{if not tagged "in_hole"
				{call "to_end"}
			}
		}
	else effector "construction"
		{delay_ex 0
			{if not tagged "in_hole"
				{tags add "contact_construction"}
				{if tagged "thickened"
					{if not tagged "ricochet"
						{if rand 0.5
							{tags add "ricochet"}
							{tags add "ricochet_short"}
						}
					}
				}
				{if tagged "ricochet"
					{if not tagged "ricocheted"
						{tags add "ricocheted"}
						{constrain_velocity 1}
						{gravity 5}
						{if tagged "thickened"
							{if not tagged "ricochet_short"
								{impulse dir -1 rnd_dir 0 50}
							else
								{impulse dir -1 rnd_dir 0 30}
							}
						else rand 0.5
							{impulse dir -1 rnd_dir 0 50}
						}
						{constrain_velocity 1}
						{delay 0.1
							{if not tagged "ricochet_short"
								{if altitude 2.5
									{tags remove "detonated"}
									{call "to_end"}
								else
									{delay 0.3
										{call "to_end"}
									}
								}
							else
								{if altitude 0.25
									{tags remove "detonated"}
								}
								{call "to_end"}
							}
						}
					}
				else
					{tags remove "detonated"}
					{call "to_end"}
				}
			else
				{if tagged "can_be_fused"
					{tags add "detonated"}
				}
				{if not tagged "thickened"
					{if rand 0.25
						{call "to_end"}
					}
				}
			}
		}
	else effector "concrete"
		{delay_ex 0
			{if not tagged "in_hole"
				{tags add "contact_construction"}
				{if tagged "thickened"
					{if not tagged "ricochet"
						{if rand 0.5
							{tags add "ricochet"}
							{tags add "ricochet_short"}
						}
					}
				}
				{if tagged "ricochet"
					{if not tagged "ricocheted"
						{tags add "ricocheted"}
						{constrain_velocity 1}
						{gravity 5}
						{if tagged "thickened"
							{if not tagged "ricochet_short"
								{impulse dir -1 rnd_dir 0 50}
							else
								{impulse dir -1 rnd_dir 0 30}
							}
						else rand 0.5
							{impulse dir -1 rnd_dir 0 50}
						}
						{constrain_velocity 1}
						{delay 0.1
							{if not tagged "ricochet_short"
								{if altitude 2.5
									{tags remove "detonated"}
									{call "to_end"}
								else
									{delay 0.3
										{call "to_end"}
									}
								}
							else
								{if altitude 0.25
									{tags remove "detonated"}
								}
								{call "to_end"}
							}
						}
					}
				else
					{tags remove "detonated"}
					{call "to_end"}
				}
			else
				{if tagged "can_be_fused"
					{tags add "detonated"}
				}
				{if not tagged "thickened"
					{if rand 0.25
						{call "to_end"}
					}
				}
			}
		}
	else
		{delay_ex 0
			{if not tagged "in_hole"
				{call "to_end"}
			}
		}
	}
)
{"flamer_fire" ; generic
	{on spawn
		{tags add "enable_contact"}
		{if tagged "end"
			{physics_work 0}
			{if not altitude -0.1
				{delay 0.01
					{delete}
				}
			else
				{call "end"}
			}
		else
			{call "specificity"}
		}
	}
	{on "specificity"
		{gravity 10}
		{delay_ex 0.01
			{add_view "fire_flamer_start" "fire1" "root"}
			{view start "fire1"}
			{delay_ex 0.01 ; 75m/s*0.02=1.5m
				{view stop "fire1"}
				{add_view "fire_flamer_main_thick" "fire2" "root"}
				{view start "fire2"}
				{tags add "valid"}
				{impulse rnd_dir 0 3 com}
				{fire radius 1.0 time 1.0 heating 5 follow}
				{delay_ex 0.03
					{tags add "can_be_fused"}
					{delay_ex 0.02 ; 75m/s*0.07=5.25m
						{volumes "body" enable contact overlap}
					}
				}
			}
		}
		{delay 0.37 ; (range+2.5)/speed = (25+2.5)m / 75m/s = 0.37
			{call "to_end"}
		}
		{delay 0.28 ; 75%
			{if not altitude 0.25
				{if not tagged "end"
					{tags add "contact_ground"}
					{call "to_end"}
				}
			}
		}
	}
	{on "in_hole" ; When it goes through the window and fence
		{if not tagged "in_hole"
			{tags add "in_hole"}
			{delay_ex 0.02
				{tags remove "in_hole"}
			}
		}
		{delay_ex 0.02 "holed"
			{tags add "ricochet"}
		; 	{volumes "body_outer" enable contact overlap}
		}
	}
	{on overlap begin
		{if not tagged "end"
			("fire_contact")
		else effector "fire_deleter"
			{if tagged "can_be_removed"
				{delete}
			}
		}
	}
	{on contact
		{if not tagged "end"
			("fire_contact")
		}
	}
	{on ground_hit
		{if not tagged "end"
			{if not tagged "valid"
				{delete}
			else
				{tags add "contact_ground"}
				{call "to_end"}
			}
		}
	}
	{on "to_end"
		{if not tagged "end"
			{tags add "end"}
			{physics_work 0}
			{volumes disable all}
			{view stop "fire0"}
			{view stop "fire1"}
			{view stop "fire2"}
			{view stop "fire_smoke"}
			{view stop "fire_smoke_small"}
			{call "end"}
		}
	}
	(define "end_fire"
		{spawn "fire_die_flamer" dir_velocity}
		{fire radius 1.0 time 0.2 heating 0.5}
		{fire radius 0.5 time 0.2 heating 1}
		{delete}
	)
	(define "end_fire_small"
		{spawn "fire_die_flamer_small" dir_velocity}
		{fire radius 0.75 time 0.2 heating 0.5}
		{fire radius 0.25 time 0.2 heating 1}
		{delete}
	)
	(define "end_explosion"
		{spawn "fire_die_exp_flamer" dir_velocity}
		{fire radius 1.5 time 0.2 heating 0.5}
		{fire radius 0.75 time 0.2 heating 1}
		{spawn "service_fire_deleter"}
		{if rand 0.9
			{tags add "can_be_removed"}
		}
		{volumes disable contact}
		{volumes enable overlap}
		{tags remove "can_be_fused"}
		{tags remove "detonated"}
		{tags remove "contact_construction"}
		{tags remove "contact_ground"}
		{tags remove "contact_vehicle"}
		{tags remove "contact_human"}
		{call "explosion"}
	)
	(define "end_explosion_small"
		{spawn "fire_die_exp_flamer_small" dir_velocity}
		{fire radius 1.0 time 0.2 heating 0.5}
		{fire radius 0.5 time 0.2 heating 1}
		{if tagged "ricochet"
			{if not tagged "ricochet_short"
				{fire radius 1.5 time 0.2 heating 10}
			}
		}
		{spawn "service_fire_deleter"}
		{if rand 0.9
			{tags add "can_be_removed"}
		}
		{volumes disable contact}
		{volumes enable overlap}
		{tags remove "can_be_fused"}
		{tags remove "detonated"}
		{tags remove "contact_construction"}
		{tags remove "contact_ground"}
		{tags remove "contact_vehicle"}
		{tags remove "contact_human"}
		{call "explosion"}
	)
	{on "end"
		{if not altitude -0.1
			{delay 0.01
				{delete}
			}
		}
		{if under_water
			{if tagged "thickened"
				("end_fire_small")
			else
				("end_fire")
			}
		else terrain_fx "water"
			{if tagged "thickened"
				("end_fire_small")
			else
				("end_fire")
			}
		else terrain_fx "shallow_water"
			{if tagged "thickened"
				("end_fire_small")
			else
				("end_fire")
			}
		else terrain_fx "puddle"
			{if tagged "thickened"
				("end_fire_small")
			else
				("end_fire")
			}
		else tagged "exploded"
			{if tagged "thickened"
				("end_explosion_small")
			else
				("end_explosion")
			}
		else tagged "detonated"
			{if rand 0.5
				{if tagged "contact_construction"
					{if tagged "thickened"
						("end_explosion_small")
					else
						("end_explosion")
					}
				else tagged "contact_ground"
					{if tagged "thickened"
						("end_explosion_small")
					else
						("end_explosion")
					}
				else tagged "contact_vehicle"
					{if tagged "thickened"
						("end_explosion_small")
					else
						("end_explosion")
					}
				else tagged "contact_human"
					{if tagged "thickened"
						("end_explosion_small")
					else
						("end_explosion")
					}
				else
					{if tagged "thickened"
						("end_fire_small")
					else
						("end_fire")
					}
				}
			else
				{if tagged "thickened"
					("end_fire_small")
				else
					("end_fire")
				}
			}
		else
			{if tagged "thickened"
				("end_fire_small")
			else
				("end_fire")
			}
		}
	}
	{on "explosion"
		{if not altitude 0.5
			{tags add "exploded"}
			{with_linked_entity "addition1"
				{call "enable_area"}
			}
		else
			{delay 0.01
				{delete}
			}
		}
		{if tagged "thickened"
			{add_view "fire_flamer_end_small" "fire3" "root"}
		else
			{add_view "fire_flamer_end" "fire3" "root"}
		}
		{view start "fire3"}
		{start_sound "weapon/shot/flame/fire"}

		{delay 0.1
			{call "burning_area"}
			{delay 0.4
				{link_sound "burn" "fire/loops/fire_medium_02"}
				{play_sound "burn" 1}
				{tags add "heavy_bruning"}
			}
		}

		{call "delete_timer"}
	}
	{on "burning_area"
		{if tagged "heavy_bruning"
			{if tagged "thickened"
				{fire radius 0.25 time 0.2 heating 20 follow}
				{fire radius 1.0 time 0.2 heating 10 follow}
				{fire radius 1.5 time 0.2 heating 1 follow}
			else
				{fire radius 0.5 time 0.2 heating 20 follow}
				{fire radius 1.5 time 0.2 heating 10 follow}
				{fire radius 2.0 time 0.2 heating 1 follow}
			}
		else
			{if tagged "thickened"
				{fire radius 0.25 time 0.2 heating 2 follow}
				{fire radius 1.0 time 0.2 heating 1 follow}
				{fire radius 1.5 time 0.2 heating 0.5 follow}
			else
				{fire radius 0.5 time 0.2 heating 2 follow}
				{fire radius 1.5 time 0.2 heating 1 follow}
				{fire radius 2.0 time 0.2 heating 0.5 follow}
			}
		}
		{delay 0.2
			{call "burning_area"}
		}
	}
	{on "delete_timer"
		{if tagged "thickened"
			{delay 15 5 ; 10-20s burning area
				{delete}
			}
		else
			{delay 5 2.5 ; 2.5-7.5s burning area
				{delete}
			}
		}
	}
}
(define "specs_fire_thin"
	{delay %koef
		{call "to_end"}
	}
	{delay (* %koef 0.75)
		{if not altitude 0.25
			{if not tagged "end"
				{tags add "contact_ground"}
				{call "to_end"}
			}
		}
	}
	{delay_ex 0
		{add_view "fire_flamer_start" "fire0" "root"}
		{add_view "fire_flamer_start_thin" "fire1" "root"}
		{view start "fire0"}
		{view start "fire1"}
	}
	{delay_ex (/ 0.75 %speed)
		{tags add "valid"}
		{impulse rnd_dir 0 3 com}
		{fire radius 0.75 time %koef heating 3 follow}
		{if rand 0.276
			{gravity (- %gravity 40)}
			{delay (- (* %koef 0.4) 0.1)
				{add_view "fire_flamer_black_smoke" "fire_smoke" "root"}
				{view start "fire_smoke"}
			}
			{delay (* %koef 0.4)
				{call "to_end"}
			}
		else rand 0.276
			{gravity (- %gravity 30)}
			{delay (- (* %koef 0.55) 0.1)
				{add_view "fire_flamer_black_smoke" "fire_smoke" "root"}
				{view start "fire_smoke"}
			}
			{delay (* %koef 0.55)
				{call "to_end"}
			}
		else rand 0.276
			{gravity (- %gravity 20)}
			{delay (- (* %koef 0.7) 0.1)
				{add_view "fire_flamer_black_smoke" "fire_smoke" "root"}
				{view start "fire_smoke"}
			}
			{delay (* %koef 0.7)
				{call "to_end"}
			}
		else rand 0.276
			{gravity (- %gravity 10)}
			{delay (- (* %koef 0.85) 0.1)
				{add_view "fire_flamer_black_smoke" "fire_smoke" "root"}
				{view start "fire_smoke"}
			}
			{delay (* %koef 0.85)
				{call "to_end"}
			}
		else
			{delay (- %koef 0.1)
				{add_view "fire_flamer_black_smoke" "fire_smoke" "root"}
				{view start "fire_smoke"}
			}
			{gravity %gravity}
		}
	}
	{delay_ex (/ 3.0 %speed)
		{view stop "fire0"}
		{add_view "fire_flamer_black_smoke" "fire_smoke" "root"}
		{view start "fire_smoke"}
		{tags add "can_be_fused"}
	}
	{delay_ex (/ 5.0 %speed)
		{add_view "fire_flamer_main_thin" "fire2" "root"}
		{view start "fire2"}
		{volumes "body" enable contact overlap}
		{fire radius 1.5 time %koef heating 3 follow}
	}
)
{"flamer_fire fire_gas" ; 70m/s, koef = 22.5/70 = 0.32
	{on "specificity" overload
		("specs_fire_thin" koef(0.32) speed(70) gravity(28.5))
	}
}
{"flamer_fire fire_liquid" ; 75m/s, koef = 27.5/75 = 0.37
	{on "specificity" overload
		("specs_fire_thin" koef(0.37) speed(75) gravity(28.5))
	}
}
{"flamer_fire fire_napalm_thin" ; 75m/s, koef = 30/75 = 0.4
	{on "specificity" overload
		("specs_fire_thin" koef(0.4) speed(75) gravity(28.5))
	}
}
{"flamer_fire fire_liquid_tank" ; 80m/s, koef = 40/80 = 0.5
	{on "specificity" overload
		("specs_fire_thin" koef(0.5) speed(80) gravity(28.5))
	}
}
(define "specs_fire_thick"
	{tags add "thickened"}
	{delay %koef
		{call "to_end"}
	}
	{delay (* %koef 0.9)
		{if not altitude 0.25
			{if not tagged "end"
				{tags add "contact_ground"}
				{call "to_end"}
			}
		}
	}
	{gravity %gravity}
	{delay_ex 0
		{add_view "fire_flamer_start" "fire1" "root"}
		{view start "fire1"}
	}
	{delay_ex (/ 0.5 %speed)
		{tags add "valid"}
		{impulse rnd_dir 0 1 com}
		{fire radius 0.5 time %koef heating 3 follow}
		{delay 0.15 0.1
			{if rand 0.25
				{add_view "fire_flamer_grey_smoke_small" "fire_smoke_small" "root"}
				{view start "fire_smoke_small"}
			}
			{if rand 0.25
				{add_view "fire_flamer_main_drops" "fire_drops" "root"}
				{view start "fire_drops"}
			}
			{delay 0.15 0.1
				{if rand 0.25
					{add_view "fire_flamer_grey_smoke_small" "fire_smoke_small" "root"}
					{view start "fire_smoke_small"}
				}
				{if rand 0.25
					{add_view "fire_flamer_main_drops" "fire_drops" "root"}
					{view start "fire_drops"}
				}
				{delay 0.15 0.1
					{if rand 0.25
						{add_view "fire_flamer_grey_smoke_small" "fire_smoke_small" "root"}
						{view start "fire_smoke_small"}
					}
					{if rand 0.25
						{add_view "fire_flamer_main_drops" "fire_drops" "root"}
						{view start "fire_drops"}
					}
				}
			}
		}
	}
	{delay_ex (/ 1 %speed)
		{add_view "fire_flamer_main_thick" "fire2" "root"}
		{view start "fire2"}
	}
	{delay_ex (/ 3 %speed)
		{view stop "fire1"}
		{tags add "can_be_fused"}
	}
	{delay_ex (/ 5 %speed)
		{volumes "body" enable contact overlap}
		{fire radius 1.0 time %koef heating 3 follow}
	}
)
{"flamer_fire fire_napalm_thick" ; 70m/s, koef = 40/70 = 0.57
	{on "specificity" overload
		("specs_fire_thick" koef(0.57) speed(70) gravity(33.5))
	}
}
{"flamer_fire fire_napalm_tank" ; 75m/s, koef = 50/75 = 0.67
	{on "specificity" overload
		("specs_fire_thick" koef(0.67) speed(75) gravity(25))
	}
}

(define "marker_contact"
	{if not tagged "valid"
		{delay_ex 0
			{if not tagged "in_hole"
				{delete}
			}
		}
	else effector "construction"
		{delay_ex 0
			{if not tagged "in_hole"
				{call "to_end"}
			}
		}
	else effector "concrete"
		{delay_ex 0
			{if not tagged "in_hole"
				{call "to_end"}
			}
		}
	else effector "human"
		{if not tagged "contact_human" ; only spawn once
			{tags add "contact_human"}
			{spawn "service_fire_fuse_human"}
		}
	else not effector "fire_service"
		{delay_ex 0
			{if not tagged "in_hole"
				{call "to_end"}
			}
		}
	}
)
{"flamer_marker" ; generic
	{on spawn
		{tags add "enable_contact"}
		{if tagged "end"
			{physics_work 0}
			{if not altitude -0.1
				{delay 0.01
					{delete}
				}
			else
				{call "end"}
			}
		else
			{call "specificity"}
		}
	}
	{on "specificity"
		{gravity 10}
		{delay_ex 0.02
			{tags add "valid"}
			{impulse rnd_dir 0 10 com}
			{delay_ex 0.02
				{volumes enable contact overlap}
			}
		}
		{delay 0.37
			{call "to_end"}
		}
		{delay 0.28
			{if not altitude 0.25
				{call "to_end"}
			}
		}
	}
	{on "in_hole" ; When it goes through the window and fence
		{if not tagged "in_hole"
			{tags add "in_hole"}
			{delay_ex 0.02
				{tags remove "in_hole"}
			}
		}
	}
	{on overlap begin
		{if not tagged "end"
			("marker_contact")
		}
	}
	{on contact
		{if not tagged "end"
			("marker_contact")
		}
	}
	{on ground_hit
		{if not tagged "end"
			{if not tagged "valid"
				{delete}
			else
				{call "to_end"}
			}
		}
	}
	{on "to_end"
		{if not tagged "end"
			{tags add "end"}
			{physics_work 0}
			{volumes disable all}
			{call "end"}
		}
	}
	{on "end"
		{if not under_water
			{spawn "service_fire_fuse"}
			{spawn "service_fire_deleter"}
		}
		{delay 0.01
			{delete}
		}
	}
}
(define "specs_marker"
	{delay %koef
		{call "to_end"}
	}
	{delay (* %koef 0.75)
		{if not altitude 0.25
			{call "to_end"}
		}
	}
	{gravity %gravity}
	{delay_ex (/ 1.0 %speed)
		{tags add "valid"}
		{impulse rnd_dir 0 10 com}
	}
	{delay_ex (/ 5.0 %speed)
		{volumes enable contact overlap}
	}
)
{"flamer_marker marker_gas"; 75m/s, koef = 22.5/75 = 0.3
	{on "specificity" overload
		("specs_marker" koef(0.3) speed(75) gravity(28.5))
	}
}
{"flamer_marker marker_liquid"; 80m/s, koef = 27.5/80 = 0.34
	{on "specificity" overload
		("specs_marker" koef(0.34) speed(80) gravity(28.5))
	}
}
{"flamer_marker marker_napalm_thin"; 80m/s, koef = 30/80 = 0.375
	{on "specificity" overload
		("specs_marker" koef(0.375) speed(80) gravity(28.5))
	}
}
{"flamer_marker marker_liquid_tank"; 85m/s, koef = 40/85 = 0.47
	{on "specificity" overload
		("specs_marker" koef(0.47) speed(85) gravity(28.5))
	}
}
{"flamer_marker marker_napalm_thick"; 75m/s, koef = 40/75 = 0.53
	{on "specificity" overload
		("specs_marker" koef(0.53) speed(75) gravity(33.5))
	}
}
{"flamer_marker marker_napalm_tank"; 80m/s, koef = 50/80 = 0.63
	{on "specificity" overload
		("specs_marker" koef(0.63) speed(80) gravity(25))
	}
}

{"fire_ground"
	{on spawn
		{if not tagged "enable_area"
			{area disable}
		}
		{tags add "enable_contact"}
	}
	{on overlap begin
		{if effector "human"
			{if tagged "obstacle_enabled"
				{kill_delay "update_obstacle"}
				{tags remove "obstacle_enabled"}
				{area disable}
			}
			{if tagged "enable_area"
				{kill_delay "update_obstacle_again"}
				{delay 0.01 "update_obstacle_again"
					{call "update_obstacle"}
				}
			}
		}
	}
	{on contact
		{if effector "human"
			{if tagged "obstacle_enabled"
				{kill_delay "update_obstacle"}
				{tags remove "obstacle_enabled"}
				{area disable}
			}
			{if tagged "enable_area"
				{kill_delay "update_obstacle_again"}
				{delay 0.01 "update_obstacle_again"
					{call "update_obstacle"}
				}
			}
		}
	}
	{on "enable_area"
		{tags add "enable_area"}
		{volumes "body" enable contact overlap visible}
		{update_visibility_patch}
		{call "update_obstacle"}
	}
	{on "update_obstacle"
		{if not tagged "obstacle_enabled"
			{tags add "obstacle_enabled"}
			{area enable}
		else
			{tags remove "obstacle_enabled"}
			{area disable}
		}
		{delay 0.01 "update_obstacle"
			{call "update_obstacle"}
		}
	}
}

{"fire_service"
	{on spawn
		{tags add "enable_contact"}
		{gravity 0}
		{physics_work 0}
		{delay 0.2
			{delete}
		}
	}
}
{"fire_deleter"
	{on spawn overload
		{tags add "enable_contact"}
		{delay 0.4
			{delete}
		}
	}
}
{"fire_addition"
	{on spawn
		{delay 0.1
			{if not linked
				{delete}
			}
		}
	}
	{on contact
		{delay 0.1
			{if not linked
				{delete}
			}
		}
	}
	{on overlap begin
		{delay 0.1
			{if not linked
				{delete}
			}
		}
	}
}
{"fire_addition fire_liquid"
	{on spawn
		{delay_ex 0.02
			{volumes enable contact}
		}
		{delay_ex 0.05
			{tags add "valid"}
		}
	}
	{on contact
		{if not tagged "valid"
			{delete}
		}
	}
}
{"fire_addition fire_napalm"
	{on spawn
		{delay_ex 0.02
			{volumes enable contact}
		}
		{delay_ex 0.05
			{tags add "valid"}
		}
	}
	{on contact
		{if not tagged "valid"
			{delete}
		}
	}
}

; Fuel tank
{"balloon"
	{inflammation_time 20}
	{on spawn
		{delay 0.01
			{volumes enable bullet blast throwing visible}
			{volumes "select" disable bullet blast throwing visible}
			{if not tagged "catching_fire"
				{call "filler_watcher"}
			}
		}
	}
	{on "drop_item"
		{if not stuff_filled "fuel" 5
			{hide 5}
		}
	}
	{on "refresh_filler"
		{tags remove "filler_known"}
	}
	{on "filler_watcher"
		{if linked "human"
			{if not tagged "filler_known"
				{tags add "filler_known"}
				{if stuff_filled "motor"
					{spawn "service_balloon_messenger_gas"}
				else stuff_filled "napalm_thick"
					{spawn "service_balloon_messenger_napalm_thick"}
				else stuff_filled "napalm_thin"
					{spawn "service_balloon_messenger_napalm_thin"}
				else stuff_filled "mixedoil"
					{spawn "service_balloon_messenger_liquid"}
				}
			}
		else linked "light_flamer"
			{if not tagged "filler_known"
				{tags add "filler_known"}
				{if stuff_filled "motor"
					{spawn "service_balloon_messenger_gas"}
				else stuff_filled "napalm_thick"
					{spawn "service_balloon_messenger_napalm_thick"}
				else stuff_filled "napalm_thin"
					{spawn "service_balloon_messenger_napalm_thin"}
				else stuff_filled "mixedoil"
					{spawn "service_balloon_messenger_liquid"}
				}
			}
		else linked
			{if not tagged "mechanized"
				{spawn "service_balloon_messenger_errorfuel"}
			else not tagged "filler_known"
				{tags add "filler_known"}
				{if stuff_filled "motor"
					{spawn "service_balloon_messenger_gas"}
				else stuff_filled "napalm_thick"
					{spawn "service_balloon_messenger_napalm_thick"}
				else stuff_filled "napalm_thin"
					{spawn "service_balloon_messenger_napalm_thin"}
				else stuff_filled "mixedoil"
					{spawn "service_balloon_messenger_liquid"}
				}
			}
		else
			{if tagged "filler_known"
				{tags remove "filler_known"}
			}
		}
		{delay 0.1
			{if not tagged "catching_fire"
				{call "filler_watcher"}
			}
		}
	}
	{on bullet_hit overload
		{if rand 0.5
			{if not linked
				{impulse up 0.4 0.2 dir 1 0.5}
			}
			{if stuff "bullet"
				{spawn "metal_hit_bul"}
			else stuff "mortar"
				{spawn "metal_hit_br"}
			else stuff "zenite"
				{spawn "metal_hit_bul"}
				{spawn "ex_air_sm"}
			else stuff "size4"
				{spawn "metal_hit_fg_big"}
			else stuff "shell small fg"
				{spawn "metal_hit_fg"}
			else stuff "shell small"
				{spawn "metal_hit_br_small"}
			else stuff "shell fg"
				{spawn "metal_hit_fg"}
			else stuff "shell"
				{spawn "metal_hit_br"}
			}
		}
	}
	{on break_armor overload}
	{on pierce overload
		{if not linked
			{if rand 0.50
				{if stuff_filled "fuel" 0
					{call "catching_fire"}
				}
			}
		else linked "human"
			{if rand 0.01
				{if stuff_filled "fuel" 0
					{call "catching_fire"}
				}
			}
		}
	}
	{on blast overload}
	{on blast_hit overload
		{if not linked
			{call "blast_physics"}
			{if min_energy 3
				{if stuff_filled "fuel" 0
					{call "explosion"}
				}
			else min_energy 0.3
				{if stuff_filled "fuel" 0
					{call "catching_fire"}
				}
			}
		else linked "human"
			{if rand 0.10
				{if min_energy 3
					{if stuff_filled "fuel" 0
						{call "explosion"}
					}
				else min_energy 0.3
					{if stuff_filled "fuel" 0
						{call "catching_fire"}
					}
				}
			}
		}
	}
	{on "burn_volume" overload
		{if not linked
			{if rand 0.50
				{if stuff_filled "fuel" 0
					{call "catching_fire"}
				}
			}
		else linked "human"
			{if rand 0.01
				{if stuff_filled "fuel" 0
					{call "catching_fire"}
				}
			}
		}
	}
	{on "catching_fire"
		{if not tagged "catching_fire"
			{tags add "catching_fire"}
			{burn volume "body" fx "smoke_dead_small1" time 8 fake even_law}
			{volumes disable touch select}
			{volumes enable visible}
			{if not linked "human"
				{explosive 1}
			}
			{delay 3.5 0.5
				{call "explosion"}
			}
			{if linked "human"
				{spawn "service_balloon_messenger_onfire" "root"}
			}
			{delay 1
				{if linked "human"
					{spawn "service_balloon_messenger_onfire" "root"}
				}
				{delay 1
					{if linked "human"
						{spawn "service_balloon_messenger_onfire" "root"}
					}
					{delay 1
						{if linked "human"
							{spawn "service_balloon_messenger_onfire" "root"}
						}
						{delay 1
							{if linked "human"
								{spawn "service_balloon_messenger_onfire" "root"}
							}
						}
					}
				}
			}
		}
	}
	(define "balloon_spawn_on_fire"
		tagged "%tag"
			{if stuff_filled "fuel" 75
				{spawn "%entity" "root" x
					{volumes disable contact}
					{tags add "exp_heavy"}
					{impulse up -0.1}
					{explosive 1}
					{call "catching_fire"}
				}
			else stuff_filled "fuel" 15
				{spawn "%entity" "root" x
					{volumes disable contact}
					{tags add "exp_light"}
					{impulse up -0.1}
					{explosive 1}
					{call "catching_fire"}
				}
			}
	)
	{on contact
		{if effector "balloon_refresher"
			{call "refresh_filler"}
		}
		{if effector "balloon_dropper"
			{if	("balloon_spawn_on_fire" tag(roks2) entity(balloon_roks2))
			else ("balloon_spawn_on_fire" tag(roks3) entity(roks3ft_tank))
			else ("balloon_spawn_on_fire" tag(wex17) entity(balloon_wex17))
			else ("balloon_spawn_on_fire" tag(m1) entity(balloon_m1))
			else ("balloon_spawn_on_fire" tag(t100) entity(t100ft_tank))
			else ("balloon_spawn_on_fire" tag(no2) entity(no2ft_tank))
			else ("balloon_spawn_on_fire" tag(fmw41) entity(fmw41_tank))
			else ("balloon_spawn_on_fire" tag(fmw35) entity(fmw35_tank))
			else ("balloon_spawn_on_fire" tag(m35) entity(m35ft_tank))
			else ("balloon_spawn_on_fire" tag(schilt) entity(schilt_tank))
			else ("balloon_spawn_on_fire" tag(m2) entity(m2ft_tank))
			}
			{delete}
		}
	}
	{on "explosion" overload
		{if not tagged "detonated"
			{tags add "detonated"}
			{if stuff_filled "fuel" 75
				{tags add "exp_heavy"}
			else stuff_filled "fuel" 15
				{tags add "exp_light"}
			}
			{if not under_water
				{if stuff_filled "fuel" 750
					{spawn "fuel_die"}
					{spawn "dummy_fire_molotov_ground"
						{delay 100 20
							{delete}
						}
					}
					{fire radius 15 time 0.2 heating 0.2}
					{fire radius 10 time 1 heating 50}
					{fire radius 7.5 time 10 heating 50}
					{blastwave c4 5 r0 4 r1 15}
				else stuff_filled "fuel" 250
					{spawn "fuel_die"}
					{spawn "dummy_fire_molotov_ground"
						{delay 80 10
							{delete}
						}
					}
					{fire radius 15 time 0.2 heating 0.2}
					{fire radius 10 time 1 heating 50}
					{fire radius 7.5 time 5 heating 50}
					{blastwave c4 5 r0 2 r1 7.5}
				else tagged "exp_heavy"
					{spawn "flamer_die"}
					{if not altitude 0.5
						{spawn "dummy_fire_molotov_ground"
							; {tags add "40-60s"}
							{delay 50 10 ; 40-60s burning area
								{delete}
							}
						}
						{fire radius 2.0 time 0.5 heating 5}
						{fire radius 1.25 time 0.5 heating 10}
						{blastwave c4 5 r0 0.2 r1 0.4}
						{blastwave c4 2 r0 1 r1 1.5}
					else
						{fire radius 1.5 time 0.5 heating 5}
						{fire radius 0.75 time 0.5 heating 10}
						{blastwave c4 5 r0 0.2 r1 0.4}
						{blastwave c4 2 r0 1 r1 1.5}
					}
				else tagged "exp_light"
					{spawn "flamer_die"}
					{if not altitude 0.5
						{spawn "dummy_fire_molotov_ground"
							; {tags add "10-30s"}
							{delay 20 10 ; 10-30s burning area
								{delete}
							}
						}
						{fire radius 2.0 time 0.25 heating 5}
						{fire radius 1.25 time 0.25 heating 10}
						{blastwave c4 2.5 r0 0.1 r1 0.2}
						{blastwave c4 1 r0 0.5 r1 0.75}
					else
						{fire radius 1.5 time 0.25 heating 5}
						{fire radius 0.75 time 0.25 heating 10}
						{blastwave c4 2.5 r0 0.1 r1 0.2}
						{blastwave c4 1 r0 0.5 r1 0.75}
					}
				else
     				{spawn "ex_grenade_sm"}
					{fire radius 1.5 time 0.25 heating 1}
					{blastwave c4 1 r0 0.5 r1 0.75}
				}
			}
			{stuff_detonate}
		}
	}
}
{"balloon_tank"
	{on spawn
		{tags add "mechanized"}
		{delay 0.01
			{if linked "vehicle"
				{bone hide "root"}
				{tags add "hidden"}
			}
		}
	}
	{on "drop_item"
		{bone show "root"}
		{tags remove "hidden"}
		{if not stuff_filled "fuel" 15
			{hide 5}
		}
	}
	{on bullet_hit overload
		{if not tagged "hidden"
			{if not linked
				{impulse up 0.4 0.2 dir 1 0.5}
			}
			{if stuff "bullet"
				{spawn "metal_hit_bul"}
			else stuff "mortar"
				{spawn "metal_hit_br"}
			else stuff "zenite"
				{spawn "metal_hit_bul"}
				{spawn "ex_air_sm"}
			else stuff "size4"
				{spawn "metal_hit_fg_big"}
			else stuff "shell small fg"
				{spawn "metal_hit_fg"}
			else stuff "shell small"
				{spawn "metal_hit_br_small"}
			else stuff "shell fg"
				{spawn "metal_hit_fg"}
			else stuff "shell"
				{spawn "metal_hit_br"}
			}
		}
	}
	{on contact
		{if effector "balloon_detonator"
			{if stuff_filled "fuel" 0
				{call "explosion"}
			}
		}
	}
}

{"balloon_service"
	{on spawn
		{delay 0.2
			{delete}
		}
	}
	{on contact overload
		{if effector "balloon"
			{volumes disable all}
		}
	}
}
{"balloon_service_human"
	{on contact overload
		{if effector "human"
			{with_effector}
			{if operatable
				{with_effector}
				{volumes disable all}
			else
				{with_effector}
			}
		else effector "vehicle"
			{with_effector}
			{if operatable
				{with_effector}
				{volumes disable all}
			else
				{with_effector}
			}
		}
	}
}
{"balloon_messenger_napalm_thick"
	{on contact overload
		{if effector "human"
			{with_effector}
			{if operatable
				{tags remove "gas"}
				{tags remove "napalm_thin"}
				{tags remove "liquid_fuel"}
				{tags add "napalm_thick"}
				{with_effector}
			else
				{with_effector}
			}
		else effector "vehicle"
			{with_effector}
			{if operatable
				{with_effector}
				{volumes disable all}
			else
				{with_effector}
			}
		}
	}
}
{"balloon_messenger_napalm_thin"
	{on contact overload
		{if effector "human"
			{with_effector}
			{if operatable
				{tags remove "gas"}
				{tags remove "napalm_thick"}
				{tags remove "liquid_fuel"}
				{tags add "napalm_thin"}
			else
				{with_effector}
			}
		else effector "vehicle"
			{with_effector}
			{if operatable
				{with_effector}
				{volumes disable all}
			else
				{with_effector}
			}
		}
	}
}
{"balloon_messenger_liquid"
	{on contact overload
		{if effector "human"
			{with_effector}
			{if operatable
				{tags remove "gas"}
				{tags remove "napalm_thin"}
				{tags remove "napalm_thick"}
				{tags add "liquid_fuel"}
				{with_effector}
			else
				{with_effector}
			}
		else effector "vehicle"
			{with_effector}
			{if operatable
				{with_effector}
				{volumes disable all}
			else
				{with_effector}
			}
		}
	}
}
{"balloon_messenger_gas"
	{on contact overload
		{if effector "human"
			{with_effector}
			{if operatable
				{tags remove "napalm_thick"}
				{tags remove "napalm_thin"}
				{tags remove "liquid_fuel"}
				{tags add "gas"}
				{with_effector}
			else
				{with_effector}
			}
		else effector "vehicle"
			{with_effector}
			{if operatable
				{with_effector}
				{volumes disable all}
			else
				{with_effector}
			}
		}
	}
}

; Molotov
{"molotov_coctail"
	{inflammation_time 20}
	{on spawn
		{delay 0.01
			{volumes enable bullet blast throwing visible}
			{volumes "select" disable bullet blast throwing visible}
		}
	}
	{on "onThrow"
		{add_view "flash_fuse_small" "fuse" "fuse"}
		{view start "fuse"}
		{delay 0.75
			{explosive 1}
		}
	}
	{on bullet_hit overload}
	{on break_armor overload}
	{on pierce overload
		{if not linked
			{if rand 0.50
				{call "detonate"}
			}
		else linked "human"
			{if rand 0.01
				{call "detonate"}
			}
		}
	}
	{on blast overload}
	{on blast_hit overload
		{if not linked
			{if min_energy 3
				{call "detonate"}
			else min_energy 0.3
				{if rand 0.50
					{call "detonate"}
				}
			}
		else linked "human"
			{if min_energy 3
				{if rand 0.10
					{call "detonate"}
				}
			else min_energy 0.3
				{if rand 0.01
					{call "detonate"}
				}
			}
		}
	}
	{on "burn_volume" overload
		{if not linked
			{if rand 0.50
				{call "detonate"}
			}
		else linked "human"
			{if rand 0.01
				{call "detonate"}
			}
		}
	}
	{on "contact_detonate" overload
		{if effector "human"
			{if not tagged "falldown"
				{tags add "falldown"}
				{constrain_velocity 1}
				{gravity 10}
				{impulse up -1}
				{constrain_velocity 1}
			}
			{delay 0.5
				{call "detonate"}
			}
		else effector "vehicle"
			{tags add "contact_vehicle"}
			{fire radius 0.5 time 40 heating 5 effector follow}
			{call "detonate"}
		else
			{tags add "contact_construction"}
			{fire radius 0.5 time 10 heating 5 effector follow}
			{call "detonate"}
		}
	}
	{on "ground_detonate" overload
		{call "detonate"}
	}
	{on "detonate" overload
		{if not tagged "detonated"
			{tags add "detonated"}
			{explosive 0}
			{if under_water
				{spawn "dummy_molotov_detonation"}
				{spawn "fire_die_flamer"}
				{fire radius 1.0 time 0.2 heating 0.5}
				{fire radius 0.5 time 0.2 heating 1}
				{delete}
			else terrain_fx "water"
				{spawn "dummy_molotov_detonation"}
				{spawn "fire_die_flamer"}
				{fire radius 1.0 time 0.2 heating 0.5}
				{fire radius 0.5 time 0.2 heating 1}
				{delete}
			else terrain_fx "shallow_water"
				{spawn "dummy_molotov_detonation"}
				{spawn "fire_die_flamer"}
				{fire radius 1.0 time 0.2 heating 0.5}
				{fire radius 0.5 time 0.2 heating 1}
				{delete}
			else terrain_fx "puddle"
				{spawn "dummy_molotov_detonation"}
				{spawn "fire_die_flamer"}
				{fire radius 1.0 time 0.2 heating 0.5}
				{fire radius 0.5 time 0.2 heating 1}
				{delete}
			else
				{if not altitude 0.5
					{explosive 0}
					{physics_work 0}
					{bone hide "root"}
					{spawn "dummy_molotov_detonation"}
					{with_linked_entity "addition1"
						{call "enable_area"}
					}
					{fire radius 2.0 time 0.5 heating 20}
					{fire radius 1.25 time 0.5 heating 30}
					{explosive 0}
				else
					{spawn "dummy_molotov_detonation"}
					{fire radius 1.5 time 0.5 heating 20}
					{fire radius 0.75 time 0.5 heating 30}
					{delete}
				}
			}
			{add_view "fire_molotov_ground" "fire" "root"}
			{view start "fire"}
			{start_sound "weapon/shot/flame/fire"}

			{delay 0.1
				{call "burning_area"}
				{delay 0.4
					{link_sound "burn" "fire/loops/fire_medium_02"}
					{play_sound "burn" 1}
					{tags add "heavy_bruning"}
				}
			}

			{delay 20 5 ; 15-25s burning area
				{delete}
			}
		}
	}
	{on "burning_area"
		{if tagged "heavy_bruning"
			{fire radius 0.85 time 0.2 heating 20 follow}
			{fire radius 1.85 time 0.2 heating 10 follow}
			{fire radius 2.50 time 0.2 heating 1 follow}
		else
			{fire radius 0.85 time 0.2 heating 2 follow}
			{fire radius 1.85 time 0.2 heating 1 follow}
			{fire radius 2.50 time 0.2 heating 0.5 follow}
		}
		{delay 0.2
			{call "burning_area"}
		}
	}
}
{"molotov_detonation"
	{on spawn
		{delay 0.01
			{stuff_detonate}
		}
	}
}
{"fire_ground_molotov"
	{on "enable_area" overload
		{tags add "enable_area"}
		{volumes "body" enable visible}
		{volumes "body_contact" enable contact overlap}
		{update_visibility_patch}
		{call "update_obstacle"}
	}
}
{"dummy fire_ground_molotov"
	{on spawn overload
		{tags add "enable_contact"}
		{if not altitude 0.5
			{if altitude 0.2
   				{pillar_up}
   				{pillar_fall}
				{delay 0.25
					{physics_work 0}
					{call "enable_area"}
				}
			else altitude 0.1
   				{pillar_up}
   				{pillar_fall}
				{delay 0.15
					{physics_work 0}
					{call "enable_area"}
				}
			else
				{physics_work 0}
				{call "enable_area"}
			}
		else
			{delay 0.01
				{delete}
			}
		}
		{add_view "fire_molotov_ground" "fire" "root"}
		{view start "fire"}
		{start_sound "weapon/shot/flame/fire"}

		{delay 0.1
			{call "burning_area"}
			{delay 0.4
				{link_sound "burn" "fire/loops/fire_medium_02"}
				{play_sound "burn" 1}
				{tags add "heavy_bruning"}
			}
		}

		{delay 60
			{delete}
		}
	}
	{on "enable_area"
		{volumes "body_contact" enable contact overlap}
	}
	{on "burning_area"
		{if tagged "heavy_bruning"
			{fire radius 0.85 time 0.2 heating 20 follow}
			{fire radius 1.85 time 0.2 heating 10 follow}
			{fire radius 2.50 time 0.2 heating 1 follow}
		else
			{fire radius 0.85 time 0.2 heating 2 follow}
			{fire radius 1.85 time 0.2 heating 1 follow}
			{fire radius 2.50 time 0.2 heating 0.5 follow}
		}
		{delay 0.2
			{call "burning_area"}
		}
	}
}

; From Robz realism mod
; Test for SRR effect
{"fx_piece_flame"
	{on spawn overload
		{volumes "body" disable contact}
		{gravity 10}
		{delay 0
			{add_view "fire_flamer_start_srre" "fire1" "root"}
			{view start "fire1"}
		}
		{delay 0.2
			{add_view "fire_flamer_main_srre" "fire2" "root"}
			{view start "fire2"}
		}
		{delay 0.05
			{volumes "body" enable contact}
			{fire radius 0.5 time 0.7 heating 1.5 follow}
		}
	}
	{on contact overload
		{volumes disable contact}
		{call "end_object"}
	}
	{on ground_hit overload
		{view stop "fire1"}
		{view stop "fire2"}
		{delay 0.1
			{call "end"}
		}
	}
	{on "end_object" overload
		{if rand 0.2
			{spawn "fire_die"}
		}
		{call "end"}
	}
	{on "end" overload
		{if rand 0.5
			{fire radius 3 time 4 heating 0.3}
			{fire radius 1.5 time 0.8 heating 0.5}
			{fire radius 1.5 time 60 heating 0.1}
			{if not air
				{if not under_water
					{spawn "fire_flamer_end_srre" dir_velocity}
				}
			}
		}
		{if terrain_fx "ground"
			{if rand 0.05
				{spawn "burn_grass1"}
			}
		}
		{if terrain_fx "grass"
			{if rand 0.05
				{spawn "burn_grass1"}
			}
		}
		{delete}
	}
}

; From Call to Arms - Gates of Hell Ostfront
; Just for test
{"fx_piece_flame_goh"
	{on spawn overload
		{volumes "body" disable contact}
		{gravity 1}
		{call "delete_time"}
		{delay 0.05
			{volumes "body" enable contact}
		}
		{delay 0.1
			{add_view "fire_flamer_start_goh" "fire2" "root"}
			{view start "fire2"}
		}
		{delay 0.3
			{add_view "fire_flamer_main_goh" "fire3" "root"}
			{view start "fire3"}
			{view stop "fire2"}
		}
	}
	{on contact overload
		{volumes disable contact}
		{fire radius 1 time 2 heating 0.5 effector follow}
		{if rand 0.2
			{spawn "fire_die"}
		}
		{call "end"}
	}
	{on ground_hit overload
		{view stop "fire2"}
		{call "ground_end"}
	}
	{on "end" overload
		{view stop "fire2"}
		{view stop "fire3"}
		{delay 0.01
			{delete}
		}
	}
	{on "ground_end" overload
		{if not under_water
			{if terrain_fx "water"
				else terrain_fx "shallow_water"
				else
				{spawn "fire_die_exp_flamer_goh" dir_velocity}
				{if rand 0.3
					{fire radius 1.2 time 20 heating 0.25}
					{spawn "fire_flamer_end_goh" offset 0 0 -10}
					{spawn "burned_spot01"}
				}
			}
		}
		{call "end"}
	}
	{on "delete_time" overload
		{delay 1.1
			{call "end"}
		}
	}
}