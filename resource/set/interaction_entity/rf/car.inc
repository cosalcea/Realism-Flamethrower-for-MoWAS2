{"car"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
	{on "mp_destroy"
		{if not tagged "destroyed"
			{damage_report "body" "component/body_broken"}
			{if not tagged "body_break"
				{components "body" break}
				{call "stat_break"}
			}
		}

		{delay 2
			{tags add "destroyed"}
			{kick_entity_manager}
		}

		{call "check_burn_emit"}
		{delay 2.3
			{view start "smoke4_1"}
		}
		{delay 30
  			{view stop "smoke4_1"}
  		}

		{reset_manual_control}
		{able select 0}
		{able repaired 0}
		{unlink_trailer}
	}
	{on contact
		{if not impregnable
			{if effector_velocity 5
				{if effector "grenade"
					{if volume "glass"
					 	{call "break_glass"}
					}
				else effector "flamer_fire"
					{if volume "glass"
					 	{call "break_glass"}
					else volume "cabin"
					 	{call "break_glass"}
					}
				}
			}
		}
	}
	{on "pierce_fuel" overload
		{if rand 0.5
			{volumes "fuel" disable bullet contact blast}
			{spawn "tank_die_particle"}
			{call "_burn"}
		}
	}
	{on "burn" overload ; disable instant burning damage
		; do nothing
	}
}

{"fuel_tank"
	{on "_explosion" overload
		; vehicle
		{call "break_all"}
		{stop_sound "move"}
		{stop_sound "move_end"}
		{stop_sound "engine"}
		{stop_sound "engine_end"}
		{stop_sound "exhaust"}
		{view stop "fire1"}
		{view stop "fire2"}
		{tags add "destroyed"}
		{kick_entity_manager}
		{call "explosion_sound"}

		{if not terrain_fx "bridge"
			{if not under_water
				{call "spawn_shellhole"}
			}
		}

		{delay_ex 0
			{set "no_burn_volumes" 1}
			{set_skeleton "_xx" sync}
			{ani_play "death"}
			{call "cut_parts"}
		}
		; car
		{add_view "smoke_dead_norm" "deathfx" "fxfire1"}
		{if not "crush"
			{spawn "tank_die" "Basis"}
			{spawn "tank_die_particle"}
			{impulse up 2.5 1.5 dir 2 1}
		}
		; flame
		{spawn "fuel_die"}
		{blastwave c4 5 r0 4 r1 15}
		{fire radius 15 time 0.2 heating 0.2}
		{fire radius 10 time 1 heating 50}
		{fire radius 7.5 time 10 heating 50}
	}
	{on "burn_volume"
		{if tagged "ignited"
			{if volume "bodyback"
				{call "_burn_bodyback"}
			}
		}
		{if tagged "ignited_thick"
			{if volume "bodyback"
				{call "_burn_bodyback"}
			}
		}
		{if tagged "ignited_molotov"
			{if volume "bodyback"
				{call "_burn_bodyback"}
			}
		}
	}
	{on "_burn_bodyback"
        {if not tagged "burned"
			{if not able "exploded"
				{chassis_work 0}
            	{add_view		"smoke_dead_norm"	"burn_fire"		"bodyback"}
				{view start "burn_fire"}
				{burn time 12}
				{tags add "burned"}
				{add_view "smoke_black" "burn_fire" "bodyback"}
				{play_sound "flame" 1}
				{view start "burn_fire"}
				{set "burn_fire" 1}
                {call "stat_break"}
				{delay 2 1
                	{call "check_burn_emit"}
                }
                {delay 4.5 1
					{fire radius 2.5 time 0.5 heating 0.1 follow}
                }
                {delay 9 2
					{able "burning" 1}
	                {explosive 1}
					{fire radius 2.5 time 0.5 heating 0.1 follow}
	            }
				{delay 10 2
					{call "mp_destroy"}
					{start_sound "crush/medium/metal"}
				}
				{delay 10 2
					{components break}
					{start_sound "crush/medium/metal"}
                	{delay 5 4
						{call "mp_destroy"}
					}
	                {explosive 1}
					{fire radius 2.5 time 0.5 heating 0.1 follow}
				}
				{delay 12
					{explosive 0}
					{view stop "burn_fire"}
					{stop_sound "flame"}
					{set "burn_fire" 0}
					{if rand 1.0
						{call "explosion"}
					else
						{able "burning" 0}
					}
				}
			}
    	}
	}
}

{"moto"
	{on "burn" overload ; disable instant burning damage
		; do nothing
	}
	{on "_burn" overload
		{add_view "smoke_dead_norm" "burn_fire" "basis"}
		{play_sound "flame" 1}
		{view start "burn_fire"}
    	{call "check_burn_emit"}
        {delay 2 1
			{fire radius 2.5 time 0.5 heating 0.1 follow}
		}
        {delay 4 1
			{explosive 1}
		}
		{delay 5 1
			{explosive 0}
			{view stop "burn_fire"}
			{stop_sound "flame"}
			{call "explosion"}
		}
		{burn time 10}
	}
}

; Flamer supply
{"flamer_distributor"
	{on spawn
		{delay 0.01
			{stuff_detonate}
		}
	}
}
{"flamer_supply_box"
	{on spawn
		{delay 0.5
			{call "mass_watcher"}
		}
	}
	{on "mass_watcher"
		{if not min_mass 3
			{volumes disable touch select}
			{delay 1.5
				{delete}
			}
		else
			{delay 0.5
				{call "mass_watcher"}
			}
		}
	}
}
{"flamer_supply"
	{on spawn
		{delay 0
			{for_each_link
				{inactive 1}
			}
		}
		{delay 3.0
			{volumes disable all}
			{damage_report "root" "component/empty"}
			{damage_report "root" "supply_info/nes"}
			{delay 2.0
				{delete}
			}
		}
	}
	{on blast_hit
		{if stuff "flamer_distributor"
			{if not tagged "inited"
				{tags add "inited"}
			else
				{volumes disable all}
				{for_each_link
					{inactive 0}
					{delay 0.2
						{impulse rnd_dir 0 2 com}
					}
				}
				{bone cut "top"}
				{delay 0.01
					{delete}
				}
			}
		}
	}
}

(define "flamer_supply_script"
	{if not tagged "supply_flamer_cd"
		{if not velocity 1
			{tags add "supply_flamer_cd"}
			{damage_report "cabin" "component/empty"}
			{damage_report "cabin" "supply_info/mfing"}
			{spawn "flashgreen" "link2" x}
			{delay 0.2
				{spawn "flashgreen" "link2" x}
				{delay 0.2
					{spawn "flashgreen" "link2" x}
				}
			}
			{spawn "%entity" "link2" x}
			{delay 3.5
				{tags remove "supply_flamer_cd"}
			}
		else
			{damage_report "cabin" "component/empty"}
			{damage_report "cabin" "supply_info/moving"}
		}
	else
		{damage_report "cabin" "component/empty"}
		{damage_report "cabin" "supply_info/cd"}
	}
)

(define "us_flamer_supply"
	{on spawn
		{tags remove "supply_flamer_cd"}
	}
	{on "supply_flamer_fuel_thick" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_fuel_m2_thick))
		else
			("flamer_supply_script" entity(service_flamer_supply_fuel_m1_thick))
		}
	}
	{on "supply_flamer_fuel_thin" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_fuel_m2_thin))
		else
			("flamer_supply_script" entity(service_flamer_supply_fuel_m1_thin))
		}
	}
	{on "supply_flamer_kit_thick" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_kit_m2_thick))
		else
			("flamer_supply_script" entity(service_flamer_supply_kit_m1_thick))
		}
	}
	{on "supply_flamer_kit_thin" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_kit_m2_thin))
		else
			("flamer_supply_script" entity(service_flamer_supply_kit_m1_thin))
		}
	}
	{on "supply_mounted_flamer_fuel_thick" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_poa_thick))
	}
	{on "supply_mounted_flamer_fuel_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_poa_thin))
	}
)
{"gmc"
	("us_flamer_supply")
}
{"gmc_art"
	("us_flamer_supply")
}
{"gmc_inf"
	("us_flamer_supply")
}

(define "ger_flamer_supply"
	{on spawn
		{tags remove "supply_flamer_cd"}
	}
	{on "supply_flamer_fuel_thin" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_fuel_fmw41))
		else
			("flamer_supply_script" entity(service_flamer_supply_fuel_fmw35))
		}
	}
	{on "supply_flamer_kit_thin" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_kit_fmw41))
		else
			("flamer_supply_script" entity(service_flamer_supply_kit_fmw35))
		}
	}
)
{"blitz3_6"
	("ger_flamer_supply")
}
{"blitz3_6art"
	("ger_flamer_supply")
}
{"blitz3_6_ger2"
	("ger_flamer_supply")
}
{"blitz3_6art_ger2"
	("ger_flamer_supply")
}
{"blitz3_6inf"
	("ger_flamer_supply")
}

(define "uk_flamer_supply"
	{on spawn
		{tags remove "supply_flamer_cd"}
	}
	{on "supply_flamer_fuel_thick" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_no2_thick))
	}
	{on "supply_flamer_fuel_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_no2_thin))
	}
	{on "supply_flamer_kit_thick" overload
		("flamer_supply_script" entity(service_flamer_supply_kit_no2_thick))
	}
	{on "supply_flamer_kit_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_kit_no2_thin))
	}
	{on "supply_mounted_flamer_fuel_thick" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_crocodile_thick))
	}
	{on "supply_mounted_flamer_fuel_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_crocodile_thin))
	}
)
{"bedford"
	("uk_flamer_supply")
}
{"bedford_art"
	("uk_flamer_supply")
}
{"bedford_inf"
	("uk_flamer_supply")
}

(define "ussr_flamer_supply"
	{on spawn
		{tags remove "supply_flamer_cd"}
	}
	{on "supply_flamer_fuel_thick" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_roks3_thick))
	}
	{on "supply_flamer_fuel_thin" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_fuel_roks3_thin))
		else
			("flamer_supply_script" entity(service_flamer_supply_fuel_roks2))
		}
	}
	{on "supply_flamer_kit_thick" overload
		("flamer_supply_script" entity(service_flamer_supply_kit_roks3_thick))
	}
	{on "supply_flamer_kit_thin" overload
		{if rand 0.95
			("flamer_supply_script" entity(service_flamer_supply_kit_roks3_thin))
		else
			("flamer_supply_script" entity(service_flamer_supply_kit_roks2))
		}
	}
)
{"zis5"
	("ussr_flamer_supply")
}
{"zis5art"
	("ussr_flamer_supply")
}
{"zis5inf"
	("ussr_flamer_supply")
}

(define "jp_flamer_supply"
	{on spawn
		{tags remove "supply_flamer_cd"}
	}
	{on "supply_flamer_fuel_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_t100))
	}
	{on "supply_flamer_kit_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_kit_t100))
	}
	{on "supply_mounted_flamer_fuel_thin" overload
		("flamer_supply_script" entity(service_flamer_supply_fuel_ssd))
	}
)
{"isuzutx40"
	("jp_flamer_supply")
}
{"isuzutx40art"
	("jp_flamer_supply")
}
{"isuzutx40_inf"
	("jp_flamer_supply")
}