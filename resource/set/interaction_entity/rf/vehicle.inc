{"vehicle"
	{inflammation_time 0.1}

	{on spawn
		{delay 0.01
			{add_view	"marker_blind" 	"marker_blind" "body"}
			{view start "marker_blind"}
			{view hide "marker_blind"}
			{if not tagged "burn_endurance_3x"
				{tags add "burn_endurance_3"}
			}
			{if not tagged "burn_endurance_2x"
				{tags add "burn_endurance_2"}
			}
			{if not tagged "burn_endurance_1x"
				{tags add "burn_endurance_1"}
			}
			{volumes "cabin" enable holed hole throwing}
			{volumes "glass" enable holed hole throwing}
		}
	}

	(define "ignited_tagger"
		{kill_delay "to_quench"}
		{tags add "ignited"}
		{if effector  "marker_thickened"
			{tags add "ignited_thick"}
		}
		{delay 1.25 0.25 "to_quench"
			{tags remove "ignited"}
			{tags remove "ignited_thick"}
		}
	)
	(define "ignited_molotov_tagger"
		{kill_delay "to_quench_molotov"}
		{tags add "ignited_molotov"}
	   	{burn fx "smoke_dead_small1" time 30 fake even_law}
		{start_sound "fire/big/big1"}
		{delay 30 "to_quench_molotov"
			{tags remove "ignited_molotov"}
		}
	)
	(define "ignited_shock_tagger"
		{if volume "body"
			{if hit_side front
				{kill_delay "remove_ignited_shock_body"}
				{tags add "ignited_shock_body"}
				{delay %time "remove_ignited_shock_body"
					{tags remove "ignited_shock_body"}
				}
			}
		}
		{if volume "turret"
			{if hit_side front
				{kill_delay "remove_ignited_shock_turret"}
				{tags add "ignited_shock_turret"}
				{delay %time "remove_ignited_shock_turret"
					{tags remove "ignited_shock_turret"}
				}
			}
		}
	)
	{on contact
		{if not impregnable
			{if effector "flamer_marker"
				{for_each_link
					{call "hit-mark-flame"}
				}
				{if not volume "sticky"
					{burn volume fx "smoke_dead_small" time 5 1 fake even_law}
				}
				{if volume "engine"
					("ignited_tagger")
				else not min_mass 20000
					("ignited_tagger")
				else tagged "classify_as_light"
					("ignited_tagger")
				else volume "body"
					{if hit_side back
						("ignited_tagger")
					}
				}
				{if effector  "marker_thickened"
					{if rand 0.05
						("ignited_shock_tagger" time(0.5))
					}
				else
					("ignited_shock_tagger" time(1.5))
				}
			else effector "molotov_coctail"
				{with_effector}
				{if tagged "fused"
					{with_effector}
					{burn volume fx "smoke_dead_small" time 40 fake even_law}
					{if volume "engine"
						("ignited_molotov_tagger")
					else not min_mass 20000
						("ignited_molotov_tagger")
					else tagged "classify_as_light"
						("ignited_molotov_tagger")
					else volume "body"
						{if hit_side back
							("ignited_molotov_tagger")
						}
					}
					("ignited_shock_tagger" time(2.0))
				else
					{with_effector}
				}
			}
		}
	}

	(define "burn_engine"
		{if rand %pe
	        {if work "engine"
	            {components "engine" break}
				{call "engine fullstop"}
				{start_sound "crush/medium/metal"}
	        }
	    }
        {if rand %pb
        	{kill_delay "regen_burn_endurance"}
        	{if not tagged "burn_endurance_cd"
        		{tags add "burn_endurance_cd"}
        		{delay 2 1
        			{tags remove "burn_endurance_cd"}
        		}

	        	{if tagged "burn_endurance_3"
					{tags add "burn_endurance_3x"}
					{tags remove "burn_endurance_3"}
				else tagged "burn_endurance_2"
					{tags add "burn_endurance_2x"}
					{tags remove "burn_endurance_2"}
				else tagged "burn_endurance_1"
					{tags add "burn_endurance_1x"}
					{tags remove "burn_endurance_1"}
				else
		            {delay 0.75 0.5
		                {call "_burn"}
		            }
		        }
		    }
		    {delay 1.05 0.05 "regen_burn_endurance"
		    	{call "burn_endurance_regeneration"}
			}
        }
    )
    (define "burn_body"
        {if rand %p
        	{kill_delay "regen_burn_endurance"}
        	{if not tagged "burn_endurance_cd"
        		{tags add "burn_endurance_cd"}
        		{delay 2 1
        			{tags remove "burn_endurance_cd"}
        		}

	        	{if tagged "burn_endurance_3"
					{tags add "burn_endurance_3x"}
					{tags remove "burn_endurance_3"}
				else tagged "burn_endurance_2"
					{tags add "burn_endurance_2x"}
					{tags remove "burn_endurance_2"}
				else tagged "burn_endurance_1"
					{tags add "burn_endurance_1x"}
					{tags remove "burn_endurance_1"}
				else
					{if not tagged "artillery"
			            {delay 0.75 0.5
			                {call "_burn"}
			            }
			        else
			        	{components "body" break}
			        	{components "turret" break}
			        	{components "gun" break}
			        }
		        }
		    }
		    {delay 1.05 0.05 "regen_burn_endurance"
		    	{call "burn_endurance_regeneration"}
			}
        }
	)
	(define "burn_shock"
		{if tagged "ignited_shock_body"
			{if rand 0.1
				{kill_delay "ignited_shock_end"}
				{tags add "shocked_flame"}
				{stunned 1}
				{if operatable
					{damage_report "body" "component/empty"}
					{damage_report "body" "flamer_info/bl"}
					{view show "marker_blind"}
				}
				{for_each_link
					{call "enable_blocker"}
				}
	            {delay 1.0 0.25 "ignited_shock_end"
					{stunned 0}
					{damage_report "body" "component/empty"}
					{for_each_link
						{call "disable_blocker"}
					}
					{view hide "marker_blind"}
                    {tags remove "shocked_flame"}
	            }
		    }
		}
		{if tagged "ignited_shock_turret"
			{if rand 0.3
				{kill_delay "ignited_shock_end"}
				{tags add "shocked_flame"}
				{stunned 1}
				{if operatable
					{damage_report "body" "component/empty"}
					{damage_report "body" "flamer_info/bl"}
					{view show "marker_blind"}
				}
				{for_each_link
					{call "enable_blocker"}
				}
	            {delay 1.0 0.25 "ignited_shock_end"
					{stunned 0}
					{damage_report "body" "component/empty"}
					{for_each_link
						{call "disable_blocker"}
					}
					{view hide "marker_blind"}
                    {tags remove "shocked_flame"}
	            }
		    }
		}
	)
	{on "burn_endurance_regeneration"
		{if not tagged "burned"
			{tags remove "burn_endurance_3x"}
			{tags remove "burn_endurance_2x"}
			{tags remove "burn_endurance_1x"}
			{tags add "burn_endurance_3"}
			{tags add "burn_endurance_2"}
			{tags add "burn_endurance_1"}
		}
	}
	{on "burn_volume" overload
		{if tagged "ignited" ; Flamethrower
			{if volume "engine"
        		{if not min_mass 20000
					("burn_engine" pe(0.02) pb(0.04))
		        else tagged "classify_as_light"
					("burn_engine" pe(0.02) pb(0.04))
				else min_mass 40000
					("burn_engine" pe(0.01) pb(0.005))
		        else
					("burn_engine" pe(0.01) pb(0.01))
	            }
	        }
            {if volume "body" ; only destroy light vehicle
        		{if tagged "sdkfz303"
					("burn_body" p(0.10))
        		else not min_mass 20000
					("burn_body" p(0.03))
				else tagged "classify_as_light"
					("burn_body" p(0.03))
				}
			}
		}
		{if tagged "ignited_thick" ; Thickened fuel extra dice
			{if volume "engine"
        		{if not min_mass 20000
					("burn_engine" pe(0.01) pb(0.01))
		        else tagged "classify_as_light"
					("burn_engine" pe(0.01) pb(0.01))
				else min_mass 40000
					("burn_engine" pe(0.01) pb(0.01))
		        else
					("burn_engine" pe(0.01) pb(0.01))
	            }
	        }
            {if volume "body" ; only destroy light vehicle
        		{if tagged "sdkfz303"
					("burn_body" p(0.05))
        		else not min_mass 20000
					("burn_body" p(0.01))
				else tagged "classify_as_light"
					("burn_body" p(0.01))
				}
			}
		}
		{if tagged "ignited_molotov" ; Molotov
			{if volume "engine"
        		{if not min_mass 20000
					("burn_engine" pe(0.03) pb(0.10))
		        else tagged "classify_as_light"
					("burn_engine" pe(0.03) pb(0.10))
				else min_mass 40000
					("burn_engine" pe(0.02) pb(0.06))
		        else
					("burn_engine" pe(0.02) pb(0.07))
	            }
	        }
            {if volume "body" ; only destroy light vehicle
        		{if tagged "sdkfz303"
					("burn_body" p(0.10))
        		else not min_mass 20000
					("burn_body" p(0.08))
				else tagged "classify_as_light"
					("burn_body" p(0.08))
				}
			}
		}

		{if volume "bodyback"
			{if rand 0.50
				{component break}
				{burn volume fx "smoke_dead_small" time 5 1 fake even_law}
			}
		}
		{if volume "wheel"
			{if rand 0.05
				{component break}
				{burn volume fx "smoke_dead_small" time 5 1 fake even_law}
			}
		}

		("burn_shock")
	}
	{on "_burn" overload
        {if not tagged "burned"
			{if not able "exploded"
				{weapon_work "gun" 0}
				{weapon_work "gun1" 0}
				{weapon_work "gun2" 0}
				{weapon_work "mgun1" 0}
				{weapon_work "mgun2" 0}
				{weapon_work "mgun3" 0}
				{weapon_work "mgun4" 0}
				{weapon_work "mgun5" 0}
				{weapon_work "flamer1" 0}
				{weapon_work "flamer2" 0}
				{weapon_work "flamer3" 0}
				{weapon_work "flamer4" 0}
				{weapon_work "flamer5" 0}
				{chassis_work 0}
				{damage_report "engine" "component/burn_engine"}
       			{if bone "engine"
            		{add_view		"smoke_dead_norm"	"burn_fire"		"engine"}
            	else bone "fxfire1"
	            	{add_view		"smoke_dead_norm"	"burn_fire"		"fxfire1"}
	            	{if bone "fxfire2"
		            	{add_view		"smoke_dead_norm"	"burn_fire"		"fxfire2"}
		            }
				else
	            	{add_view		"smoke_dead_norm"	"burn_fire"		"body"}
				}
				{view start "burn_fire"}
				{burn time 12}
				{tags add "burned"}
       			{if bone "engine"
					{add_view "smoke_black" "burn_fire" "engine"}
            	else bone "fxfire1"
					{add_view "smoke_black" "burn_fire" "fxfire1"}
					{if bone "fxfire2"
						{add_view "smoke_black" "burn_fire" "fxfire2"}
					}
				else
					{add_view "smoke_black" "burn_fire" "body"}
				}
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
					{components "engine" break}
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
					{if rand 0.5
						{call "explosion"}
					else
						{able "burning" 0}
					}
				}
			}
    	}
	}
	{on "burn_emit" overload
        {reset_manual_control}
        {talk "burning"}
        {delay 0.5
            {crew_emit}
            {delay 0.5
                {crew_emit}
                {delay 0.5
                    {crew_emit}
	                {delay 0.5
	                    {crew_emit}
		                {delay 0.5
		                    {crew_emit}
		                    {delay 0.5
		                        {crew_emit}
				                {delay 0.5
				                    {crew_emit}
					                {delay 0.5
					                    {crew_emit}
						                {delay 0.5
						                    {crew_emit}
							                {delay 0.5
							                    {crew_emit}
								                {delay 0.5
								                	{kill_crew}
								                }
							                }
						                }
					                }
				                }
		                    }
		                }
	                }
                }
            }
        }
	}

	{on "engine fullstop"}

	{on "supply_flamer_fuel_thick"
		{damage_report "body" "component/empty"}
		{damage_report "body" "supply_info/ua"}
	}
	{on "supply_flamer_fuel_thin"
		{damage_report "body" "component/empty"}
		{damage_report "body" "supply_info/ua"}
	}
	{on "supply_flamer_kit_thick"
		{damage_report "body" "component/empty"}
		{damage_report "body" "supply_info/ua"}
	}
	{on "supply_flamer_kit_thin"
		{damage_report "body" "component/empty"}
		{damage_report "body" "supply_info/ua"}
	}
	{on "supply_mounted_flamer_fuel_thick"
		{damage_report "body" "component/empty"}
		{damage_report "body" "supply_info/ua"}
	}
	{on "supply_mounted_flamer_fuel_thin"
		{damage_report "body" "component/empty"}
		{damage_report "body" "supply_info/ua"}
	}
}

{"pg1"
	{on "_burn"
		{add_view "smoke_dead_norm" "burn_fire" "fx_fire1"}
		{view start "burn_fire"}
	}
}

{"shoot_blocker_shock"
	{on "enable_blocker"
		{for_each_link
			{volumes enable bullet}
		}
	}
	{on "disable_blocker"
		{for_each_link
			{volumes disable bullet}
		}
	}
}
{"shoot_blocker_flamer"
	{on "enable_flamer_blocker"
		{for_each_link
			{volumes enable bullet}
		}
	}
	{on "disable_flamer_blocker"
		{for_each_link
			{volumes disable bullet}
		}
	}
}