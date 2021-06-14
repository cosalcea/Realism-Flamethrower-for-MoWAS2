{"human"
	{inflammation_time 0.1}
	{on spawn
		{call "burn_fx_init"}
		{tags remove "flamer_deadzone"}
		{if tagged "flamer"
			{delay 0.05 "refresh_balloon"
				{spawn "service_balloon_refresher" "body" x}
			}
		}
	}
	{on operatable on
		{if tagged "flamer"
			{delay 0.05 "refresh_balloon"
				{spawn "service_balloon_refresher" "body" x}
			}
		}
	}

	(define "health_damage"
		{if not dead
			{if not tagged "bleeding"
				{health_damage_count %c
					{effects "" "hit" "damage" "die" "die"}
				}
			else
				{call "kill_bleeding"}
			}
		}
	)
	(define "health_damage_flame"
		{if not under_water
			{if not dead
				{if not tagged "bleeding"
					{burn}
					{health_damage_count %c
						{effects "" "hit-flame" "hit-flame" "_burn" "_burn"}
					}
					{if not able "burning"
						{burn stop_retry}
					}
				else
					{call "kill_bleeding_flame"}
				}
			}
		else
			{if not dead
				{if not tagged "bleeding"
					{burn}
					{health_damage_count (/ %c 10)
						{effects "" "hit-flame" "hit-flame" "_burn" "_burn"}
					}
					{if not able "burning"
						{burn stop_retry}
					}
				else
					{call "kill_bleeding_flame"}
				}
			}
		}
	)
	{on "process_bullet_hit" overload
		{if hit_side front	{kill_flags front}
		else hit_side back	{kill_flags back}
		else				{kill_flags front back}
		}
		{if velocity 7		{kill_flags run}
		else velocity 0.1	{kill_flags go}
		}
		{kill_flags piercing}
		{if	stuff "rifle"	{kill_flags rifle}}
		{if	stuff "mgun"	{kill_flags mgun}}
		{if	stuff "smg"	{kill_flags smg}}
		{if	stuff "pistol"	{kill_flags pistol}}

		{if not dead
			{if not tagged "bleeding"
				{health_damage_pierce
					{effects	"hit-scream"
								"hit-light" "hit-heavy"
								"die" "hit-explosion"
								"throw-off" "throw-off-and-die"
					}
					{explosive_treshold 70} ; useless for bullet_hit
					{table {30 1} {200 2.5} {500 3} {5000 5}} ; {projectileDamage throw_force}
					; ※require "projectileDamage", "projectileDamageTable" can not trigger the throwing.
				}
			else
				{call "kill_bleeding"}
			}
		}
	}
	{on blast_hit overload
		{if min_energy 0.8
			("health_damage" c(100))
		}
		{if stuff "kamikaze"
			{call "die"}
			("health_damage" c(250))
			{con "kamikaze"}
		}

		{kill_flags reset}
		{if hit_side front	{kill_flags front}
		else hit_side back	{kill_flags back}
	    else				{kill_flags front back}
	    }
		{kill_flags blast}

		{if not dead
			{if not tagged "bleeding"
				{health_damage_blast
					{effects	"hit-scream"
								"hit-light" "hit-heavy"
								"die" "hit-explosion"
								"throw-off" "throw-off-and-die"
					}
					{table {2.5 0.5} {10 1} {50 3} {250 6}} ; {energy throw_force}
					; Even if the blastwave has not dealt enough damage to kill the soldier,
					; the "throw-off-and-die" triggered by blastwave will kill him after throwing often.
				}
			else
				{call "kill_bleeding"}
			}
		}
	}

	(define "contact_balloon_service"
		{if effector "balloon_messenger_onfire"
			{if tagged "flamer"
				{damage_report "head" "component/empty"}
				{damage_report "head" "flamer_info/cf"}
				{delay 0.75 0.25
					{if operatable
						{spawn "service_balloon_dropper" "body"}
						{damage_report "head" "component/empty"}
						{damage_report "head" "flamer_info/dc"}
					}
				}
			}
		else effector "balloon_messenger_napalm_thick"
			{tags remove "gas"}
			{tags remove "napalm_thin"}
			{tags remove "liquid_fuel"}
			{tags add "napalm_thick"}
		else effector "balloon_messenger_napalm_thin"
			{tags remove "gas"}
			{tags remove "napalm_thick"}
			{tags remove "liquid_fuel"}
			{tags add "napalm_thin"}
		else effector "balloon_messenger_liquid"
			{tags remove "gas"}
			{tags remove "napalm_thin"}
			{tags remove "napalm_thick"}
			{tags add "liquid_fuel"}
		else effector "balloon_messenger_gas"
			{tags remove "napalm_thick"}
			{tags remove "napalm_thin"}
			{tags remove "liquid_fuel"}
			{tags add "gas"}
		else
		; do nothing
		}
	)
	(define "contact_crush"
		{if not tagged "contact_cooldown1" ; 0.2s cooldown
			{tags add "contact_cooldown1"}
			{kill_flags reset}
			{if effector_velocity %v
				{if not dead
					{if not tagged "bleeding"
						{health_damage_count %d
							{effects "" "hit" "hit" "die" "die"}
						}
					else
						{call "kill_bleeding"}
					}
				else
					{if rand %pb
						{spawn "bloodsparks_small"}
					}
					{if rand %pc
						{call "crush"}
					}
				}
			}
			{delay 0.2
				{tags remove "contact_cooldown1"}
			}
		}
	)
	(define "contact_hit"
		{if not tagged "contact_cooldown1" ; 0.2s cooldown
			{tags add "contact_cooldown1"}
			{kill_flags reset}
			{if contact_velocity 5
				{if not dead
					{if not tagged "bleeding"
						{health_damage_count 0
							{effects "" "hit" "hit" "hit" "hit"}
						}
					}
				}
			}
			{delay 0.2
				{tags remove "contact_cooldown1"}
			}
		}
	)
	(define "contact_stab"
		{if not tagged "contact_cooldown1" ; 0.2s cooldown
			{tags add "contact_cooldown1"}
			{kill_flags reset}
			{with_effector}
			{if tagged "sharp"
				{with_effector}
				{if not dead
					{if not tagged "bleeding"
						{if volume "head"
							{health_damage_count 500
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else volume "body"
							{health_damage_count 500
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else
							{health_damage_count 100
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						}
					else
						{call "kill_bleeding"}
					}
				}
			else
				{with_effector}
				{if not dead
					{if not tagged "bleeding"
						{if volume "head"
							{health_damage_count 100
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else volume "body"
							{health_damage_count 100
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else
							{health_damage_count 50
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						}
					else
						{call "kill_bleeding"}
					}
				}
			}
			{delay 0.2
				{tags remove "contact_cooldown1"}
			}
		}
	)
	(define "contact_axe"
		{if not tagged "contact_cooldown1" ; 0.2s cooldown
			{tags add "contact_cooldown1"}
			{kill_flags reset}
			{with_effector}
			{if tagged "sharp"
				{with_effector}
				{if not dead
					{if not tagged "bleeding"
						{if volume "head"
							{health_damage_count 500
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else volume "body"
							{health_damage_count 500
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else
							{health_damage_count 200
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						}
					else
						{call "kill_bleeding"}
					}
				}
			else
				{with_effector}
				{if not dead
					{if not tagged "bleeding"
						{if volume "head"
							{health_damage_count 200
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else volume "body"
							{health_damage_count 200
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						else
							{health_damage_count 100
								{effects "" "hit" "damage" "die_from_knife" "die_from_knife"}
							}
						}
					else
						{call "kill_bleeding"}
					}
				}
			}
			{delay 0.2
				{tags remove "contact_cooldown1"}
			}
		}
	)
	(define "contact_part"
		{if not tagged "contact_cooldown2" ; 2s cooldown, vanilla
			{tags add "contact_cooldown2"}
			{kill_flags reset}
			{if effector_velocity %v
				{if not dead
					{if not tagged "bleeding"
						{if not linked
							{if volume "head"
								("health_damage" c(%d))
							else volume "body"
								("health_damage" c(%d))
							}
						}
						("health_damage" c(%d))
					else
						{call "kill_bleeding"}
					}
				}
			}
			{delay 2
				{tags remove "contact_cooldown2"}
			}
		}
	)
	{on contact overload
		{if effector "balloon_service"  ; contact without cooldown
			("contact_balloon_service")
		else effector "fire_ground"
			; do nothing
		else not impregnable
			{if effector "flamer_marker"
				{call "hit-mark-flame"}
			else effector "flamer_blocker"
				; see {"flamer_blocker"}
			else effector "tank"  ; contact with cooldown
				("contact_crush" v(3) d(100) pb(0.25) pc(0.25))
			else effector "armored_car"
				("contact_crush" v(3) d(75) pb(0.1) pc(0.1))
			else effector "vehicle"
				("contact_crush" v(3) d(50) pb(0.1) pc(0))
			else effector "chicken"
				("contact_hit")
			else effector "molotov_coctail"
				("contact_hit")
			else effector "knife"
				("contact_stab")
			else effector "axe"
				("contact_axe")
			else effector "building_part"
				("contact_part" v(6) d(120))
			else effector "big part"
				("contact_part" v(6) d(120))
			else effector "medium part"
				("contact_part" v(6) d(80))
			else effector "small part"
				("contact_part" v(10) d(40))
			else effector "wire"
				("contact_part" v(3) d(10))
			}
		}
	}

	{on "add_burn_fx" overload}
	{on "burn_fx_init"
		{add_view "smoke_dead_small" "burn_fire" "body"}
		{add_view "smoke_dead_small" "burn_fire" "hand1l"}
		{add_view "smoke_dead_small" "burn_fire" "hand1r"}
		{add_view "smoke_dead_small" "burn_fire" "foot2l"}
		{add_view "smoke_dead_small" "burn_fire" "foot2r"}
		{if able "burning"
			{view start "burn_fire"}
			{tags add "on_fire"}
		else
			{view stop "burn_fire"}
			{tags remove "on_fire"}
		}
	}
	{on "hit-mark-flame"
		{if not able "burning"
			{kill_delay "to_quench"}
			{tags add "ignited"}
			{if terrain_fx "water"
				("health_damage_flame" c(5.0))
			else terrain_fx "shallow_water"
				("health_damage_flame" c(5.0))
			}
			{delay 1.5 "to_quench"
				{tags remove "ignited"}
			}
		}
	}
	{on "hit-flame"
		{if operatable
			{if not able "burning"
				{if not tagged "burn_injuring"
					{tags add "burn_injuring"}
					{talk "burn_injuring"}
					{delay 1.25 0.25
						{tags remove "burn_injuring"}
					}
				}
			}
		}
	}
	{on "on-fire-napalm" ; abandoned
		{if not able "burning"
			{kill_delay "stop_on_fire"}
			{if not tagged "on_fire"
				{add_view "smoke_dead_small" "burn_fire"	"body"}
				{add_view "smoke_dead_small" "burn_fire"	"hand1l"}
				{add_view "smoke_dead_small" "burn_fire"	"hand1r"}
				{add_view "smoke_dead_small" "burn_fire"	"foot2l"}
				{add_view "smoke_dead_small" "burn_fire"	"foot2r"}
				{view start "burn_fire"}
				{tags add "on_fire"}
			}
			{delay 3.0 "stop_on_fire"
				{if not able "burning"
					{view stop "burn_fire"}
					{tags remove "on_fire"}
				}
			}
		}
	}
	{on "on-fire-liquid" ; abandoned
		{if not able "burning"
			{kill_delay "stop_on_fire"}
			{if not tagged "on_fire"
				{add_view "smoke_dead_small" "burn_fire"	"body"}
				{add_view "smoke_dead_small" "burn_fire"	"hand1l"}
				{add_view "smoke_dead_small" "burn_fire"	"hand1r"}
				{add_view "smoke_dead_small" "burn_fire"	"foot2l"}
				{add_view "smoke_dead_small" "burn_fire"	"foot2r"}
				{view start "burn_fire"}
				{tags add "on_fire"}
			}
			{delay 1.5 "stop_on_fire"
				{if not able "burning"
					{view stop "burn_fire"}
					{tags remove "on_fire"}
				}
			}
		}
	}
	{on "on-fire"
		{kill_delay "stop_on_fire"}
		{if not tagged "on_fire"
			{add_view "smoke_dead_small" "burn_fire"	"body"}
			{add_view "smoke_dead_small" "burn_fire"	"hand1l"}
			{add_view "smoke_dead_small" "burn_fire"	"hand1r"}
			{add_view "smoke_dead_small" "burn_fire"	"foot2l"}
			{add_view "smoke_dead_small" "burn_fire"	"foot2r"}
			{view start "burn_fire"}
			{tags add "on_fire"}
		}
	}
	{on "burn_volume" overload
		{if not able "burning"
			{if tagged "in_hatch"
				; no damage
			else tagged "ignited"
				("health_damage_flame" c(7.5))
			else
				{if not linked
					{if volume "head"
						("health_damage_flame" c(3.0))
					else volume "body"
						("health_damage_flame" c(3.0))
					else
						("health_damage_flame" c(1.5))
					}
					; {tags add "debug1"}
				else linked "cannon"
					{if volume "head"
						("health_damage_flame" c(3.0))
					else volume "body"
						("health_damage_flame" c(3.0))
					else
						("health_damage_flame" c(1.5))
					}
					; {tags add "debug2"}
				else altitude 0.75
					{if volume "head"
						("health_damage_flame" c(3.0))
					else volume "body"
						("health_damage_flame" c(1.5))
					}
					; {tags add "debug3"}
				else
					{if volume "head"
						("health_damage_flame" c(1.5))
					}
					; {tags add "debug4"}
				}
			}
		}
	}
	{on "burn_scream" overload
		{talk "burn_cry"}
	}
	{on "burn_linked"
        {delay 0.5
			{get_off}
	        {delay 0.5
				{get_off}
		        {delay 0.5
					{get_off}
			        {delay 0.5
						{get_off}
				        {delay 0.5
							{get_off}
				        }
			        }
		        }
	        }
        }
		{delay 2.5 0.5
			{if not lying
				{chassis_work 0}
				{knockdown 0}
				{if not dead
					{ani_play "die_gas_dark_sintera" 0.75 resume}
					{ani_play "die_flame_dark_sintera" 2.0 resume}
				}
			}
		}
	}
	{on "die_throw_burn"
		{kill_flags reset}
		{kill_flags piercing}
		{tags add "burned"}
		{throw_off up 0 1.5 dir 0 1.5 die}
	}
	{on "_burn" overload ; burn to death
		{if not dead
			{if not able "burning"
				{able "burning" 1}
				{health_damage_count -5 ; Reserve for triggering events.
					{effects "" "" "" "" ""}
				}
				{burn time 10}
				; total burn time, using for flag checking.
				; Any soldier was killed in this duration will be identified as "burned" death.
				; Any soldier can not be burned again with this flag.
				; "{burn stop_retry}" can reset this flag.

				{call "on-fire"}
				{delay 0.2 0.1 "to_burn_scream"
					{call "burn_scream"}
				}

				{weapon_work "hand_right" 0}
				{able "select" 0}
				{drop_orders}

				{if boarding
					{kill_delay "to_burn_scream"}
					{call "burn_scream"}
					{health_damage_count 500
						{effects "" "die_throw_burn" "die_throw_burn" "die_throw_burn" "die_throw_burn"}
					}
				else linked "tree"
					{chassis_work 0}
					{delay 0.4 0.1
						{if not dead
							{ani_play "die_gas_dark_sintera" 0.75 resume}
							{ani_play "die_flame_dark_sintera" 2.0 resume}
						}
					}
				else linked "construction"
					{chassis_work 0}
					{delay 0.4 0.1
						{if not dead
							{ani_play "die_gas_dark_sintera" 0.75 resume}
							{ani_play "die_flame_dark_sintera" 2.0 resume}
						}
					}
				else linked
					{call "burn_linked"}
				else terrain_fx "water"
					{chassis_work 0}
					{delay 0.4 0.1
						{if not dead
							{ani_play "die_gas_dark_sintera" 0.75 resume}
							{ani_play "die_flame_dark_sintera" 2.0 resume}
						}
					}
				else terrain_fx "shallow_water"
					{chassis_work 0}
					{delay 0.4 0.1
						{if not dead
							{ani_play "die_gas_dark_sintera" 0.75 resume}
							{ani_play "die_flame_dark_sintera" 2.0 resume}
						}
					}
				else
					{delay 1.25 0.25
						{if not lying
							{chassis_work 0}
							{knockdown 0}
							{if not dead
								{ani_play "die_gas_dark_sintera" 0.75 resume}
								{ani_play "die_flame_dark_sintera" 2.0 resume}
							}
						}
					}
				}

				{delay 3.5 0.5
					{kill_flags reset}
					{kill_flags piercing}
					{tags add "burned"}
					{if not linked
						{health_damage_count 500
							{effects "" "die" "die" "die" "die"}
						}
					else
						{health_damage_count 500
							{effects "" "die_throw_burn" "die_throw_burn" "die_throw_burn" "die_throw_burn"}
						}
					}
					{delay 0.5
						{view stop "burn_fire"}
						{tags remove "on_fire"}
						{if dead
							{if terrain_fx "puddle"
								{call "stop_burn"}
							else terrain_fx "shallow_water"
								{call "stop_burn"}
							else terrain_fx "water"
								{call "stop_burn"}
							else
								{if not tagged "burned_fire"
									{add_view "smoke_dead_small1" "burned_fire" "body"}
									{add_view "smoke_dead_small1" "burned_fire" "hand1l"}
									{add_view "smoke_dead_small1" "burned_fire" "hand1r"}
									{add_view "smoke_dead_small1" "burned_fire" "foot2l"}
									{add_view "smoke_dead_small1" "burned_fire" "foot2r"}
									{view start "burned_fire"}
									{tags add "burned_fire"}
								}
								{delay 12.5 2.5
									{view stop "burned_fire"}
									{tags remove "burned_fire"}
									{call "stop_burn"}
								}
							}
						else
							{call "stop_burn"}
						}
					}
				}
			}
		}
	}
	{on "stop_burn" overload
		{ani_stop "die_gas_dark_sintera"}
		{ani_stop "die_flame_dark_sintera"}
		{able "burning" 0}

		{if not dead
			{tags remove "burned"}
			{chassis_work 1}
			{weapon_work "hand_right" 1}
			{able "select" 1}
		}

		{delay 1.5
			{burn stop_retry}
		}
	}

	{on "link_weapon" overload
		{view hide	"flashbarrel"}
		{view pause	"flashbarrel"}

		{view hide	"firebarrel"}
		{view pause	"firebarrel"}
		{view stop	"flamermark"}
		{view stop	"flamershot"}
		{tags remove "flamer_loaded"}
		{tags remove "flamer"}

		{if stuff "pistol"
			{add_view "flash_gun_small" "flashbarrel" "foresight3"}
			{add_view "shell_smg"			"shell"			"FXshell"}
		else stuff "shotgun"
			{add_view "flash_gun_big" "flashbarrel" "foresight3"}
			{add_view "shell_shotgun"			"shell"			"FXshell"}
		else stuff "rifle"
			{add_view "flash_gun_small" "flashbarrel" "foresight3"}
			{add_view "shell_mgun"			"shell"			"FXshell"}
		else stuff "smg"
			{add_view "flash_gun_small" "flashbarrel" "foresight3"}
			{add_view "shell_smg"			"shell"			"FXshell"}
		else stuff "mgun"
			{add_view "flash_gun_big" "flashbarrel" "foresight3"}
			{add_view "shell_mgun"			"shell"			"FXshell"}
		else stuff "flame_thrower"
			{tags add "flamer"}
			{delay 0.05 "refresh_balloon"
				{spawn "service_balloon_refresher" "body" x}
			}
			{add_view "flamer_muzzle" "firebarrel" "foresight3"}
			{view show	"firebarrel"}
			{view start	"firebarrel"}
			{add_view "flamer_flash" "flashbarrel" "foresight3"}
			{link_sound "flamer_start" "weapon/shot/flame/goh/handheld/flamer_start"}
			{link_sound "flamer_loop" "weapon/shot/flame/goh/handheld/flamer_loop"}
			{link_sound "flamer_stop" "weapon/shot/flame/goh/handheld/flamer_stop"}
			{call "flamer_deadzone_checker"}
		}
	}
	{on fire "hand_right" overload
		; Generic
		{kill_delay "fire"}
		{kill_delay "shell"}
		{view show	"flashbarrel"}
		{view start	"flashbarrel"}
		{view start "shell"}
		{delay 0.4 "fire"
			{view hide	"flashbarrel"}
			{view pause	"flashbarrel"}
		}
		{delay 0.1 "shell"
			{view pause "shell"}
		}
		; Flamethrower
		{if tagged "flamer"
			{if bone "foresight3"
				; Sound
				{kill_delay "stop_playing_flamer"}
				{if not tagged "played_flamer_start"
					{tags add "played_flamer_start"}
					{play_sound "flamer_start"}
				}
				{if not tagged "playing_flamer_loop"
					{tags add "playing_flamer_loop"}
					{delay 0.05
						{play_sound "flamer_loop" 1}
					}
				}
				{delay 0.1 "stop_playing_flamer"
					{stop_sound "flamer_loop"}
					{play_sound "flamer_stop"}
					{tags remove "played_flamer_start"}
					{tags remove "playing_flamer_loop"}
				}
				; Fire
				{kill_delay "flamershot"}
				{if not tagged "flamer_deadzone"
					{if not tagged "flamer_loaded"
						{tags add "flamer_loaded"}
						{if tagged "napalm_thick"
							{add_view "flamer_marker_napalm_thick" "flamermark" "foresight3"}
							{add_view "flamer_fire_napalm_thick" "flamershot" "foresight3"}
						else tagged "napalm_thin"
							{add_view "flamer_marker_napalm_thin" "flamermark" "foresight3"}
							{add_view "flamer_fire_napalm_thin" "flamershot" "foresight3"}
						else tagged "liquid_fuel"
							{add_view "flamer_marker_liquid" "flamermark" "foresight3"}
							{add_view "flamer_fire_liquid" "flamershot" "foresight3"}
						else
							{add_view "flamer_marker_gas" "flamermark" "foresight3"}
							{add_view "flamer_fire_gas" "flamershot" "foresight3"}
						}
					}
					{view start	"flamermark"}
					{view start	"flamershot"}
				}
				{delay 0.1 "flamershot"
					{view stop	"flamermark"}
					{view stop	"flamershot"}
					{tags remove "flamer_loaded"}
				}
			}
		}
		; Rocket launcher
		{spawn "bazooka_shot" "fxshot" x}
	}
	{on "flamer_deadzone_checker"
		{if tagged "flamer"
			{if operatable
				{if bone "foresight3"
					{spawn "service_flamer_blocker" "foresight3" x
						{impulse forward 0.2 com}
					}
				}
			}
		}
		{delay 0.1
			{if tagged "flamer"
				{call "flamer_deadzone_checker"}
			}
		}
	}
	{on "start_ammo_refill"
		{if tagged "flamer"
			{delay 0.05 "refresh_balloon"
				{spawn "service_balloon_refresher" "body" x}
			}
		}
	}

	{on move on
		{view stop	"flamermark"}
		{view stop	"flamershot"}
		{tags remove "flamer_loaded"}
		{if tagged "in_hatch"
			{tags remove "in_hatch"}
			{call "out_hatch"}
		}
	}
	{on turn on
		{view stop	"flamermark"}
		{view stop	"flamershot"}
		{tags remove "flamer_loaded"}
		{if tagged "in_hatch"
			{tags remove "in_hatch"}
			{call "out_hatch"}
		}
	}
	{on movement_mode_changed
		{view stop	"flamermark"}
		{view stop	"flamershot"}
		{tags remove "flamer_loaded"}
		{if tagged "in_hatch"
			{tags remove "in_hatch"}
			{call "out_hatch"}
		}
	}
	{on board in
		{view stop	"flamermark"}
		{view stop	"flamershot"}
		{tags remove "flamer_loaded"}
	}
	{on board out
		{if tagged "in_hatch"
			{tags remove "in_hatch"}
			{call "out_hatch"}
		}
	}
	{on "out_hatch"}

	{on "die_without_blood" overload
		{view pause "swim"}
		{if not kill_flags blast
			{kill_flags piercing}
		}
		{if tagged "burned"
			{view stop	"flamermark"}
			{view stop	"flamershot"}
			{tags remove "flamer_loaded"}
			; {tags remove "flamer"} ; to fix revival bug
			{able "personage" 0}
			{tex_morph "burned" 3}
			{ani_stop "die_gas_dark_sintera"}
			{ani_stop "die_flame_dark_sintera"}
			{die}
		else
			{call "die_scream"}
			{view stop	"flamermark"}
			{view stop	"flamershot"}
			{tags remove "flamer_loaded"}
			; {tags remove "flamer"} ; to fix revival bug
			{ani_stop "die_gas_dark_sintera"}
			{ani_stop "die_flame_dark_sintera"}
			{die}
		}
		{delay 3
			{volumes enable contact}
		}
	}

	{on "start_personage"
		{health_damage_count -5 ; Reserve for triggering events.
			{effects "" "" "" "" ""}
		}
	}
	{on "kill_bleeding"
		{health_damage_count 500
			{effects "" "" "" "bleeding_kill" "bleeding_kill"}
		}
	}
	{on "kill_bleeding_flame"
		{burn}
		{health_damage_count 500
			{effects "" "" "" "bleeding_kill" "bleeding_kill"}
		}
		{if not able "burning"
			{burn stop_retry}
		}
	}
	{on "bleeding_kill"
		{tags remove "bleeding"}
		{able "personage" 0} ; killing the bleeding soldier
		{die}
		{tags remove "bleeding"}
	}
}

{"flamer_blocker"
	{on spawn
		{gravity 0}
		{delay 0.1
			{delete}
		}
	}
	{on "in_hole"
		{tags add "by_hole"}
	}
	{on contact
		{if not effector "human"
			{delay_ex 0
				{if not tagged "by_hole"
					{volumes "blocker" enable contact}
					{volumes "blocker2" enable contact}
				}
			}
		else volume "blocker"
			{with_effector}
			{if tagged "flamer"
				{kill_delay "flamer_deadzone"}
				{tags add "flamer_deadzone"}
				{view stop	"flamermark"}
				{view stop	"flamershot"}
				{tags remove "flamer_loaded"}
				{delay 0.1 "flamer_deadzone"
					{tags remove "flamer_deadzone"}
				}
			}
			{with_effector}
		}
	}
}

{"physics_damping"
	{on "onThrow"
		{tags add "sharp"}
		{delay 0.5
			{tags remove "sharp"}
		}
	}
}