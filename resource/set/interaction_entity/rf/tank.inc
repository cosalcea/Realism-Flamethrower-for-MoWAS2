{"tank"
	{inflammation_time 0.1}
}

{"vehicle"
	{on "start_ammo_refill"
		{if tagged "flamer"
			{delay 0.05 "refresh_balloon"
				{spawn "service_balloon_refresher" "body" x}
				{delay 0.05 "refresh_balloon"
					{spawn "service_balloon_refresher" "body" x}
					{delay 0.05 "refresh_balloon"
						{spawn "service_balloon_refresher" "body" x}
					}
				}
			}
		}
	}
}
(define "fuel_checker_light"
	{on contact
		{if effector "balloon_messenger_napalm_thick"
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
		}
	}
)
(define "fuel_checker_heavy"
	{on contact
		{if effector "balloon_messenger_errorfuel"
			{call "errorfuel"}
		}
		{if effector "balloon_messenger_napalm_thick"
			{tags remove "gas"}
			{tags remove "napalm_thin"}
			{tags remove "liquid_fuel"}
			{tags add "napalm_thick"}
		else effector "balloon_messenger_napalm_thin"
			{tags remove "gas"}
			{tags remove "napalm_thin"}
			{tags remove "napalm_thick"}
			{tags add "liquid_fuel"}
		else effector "balloon_messenger_liquid"
			{tags remove "gas"}
			{tags remove "napalm_thin"}
			{tags remove "napalm_thick"}
			{tags add "liquid_fuel"}
		else effector "balloon_messenger_gas"
			{tags remove "gas"}
			{tags remove "napalm_thin"}
			{tags remove "napalm_thick"}
			{tags add "liquid_fuel"}
		}
	}
	{on "errorfuel"
		{kill_delay "errorfuel_reset"}
		{if operatable
			{damage_report "body" "component/empty"}
			{damage_report "body" "flamer_info/ef"}
		}
		{for_each_link
			{call "enable_flamer_blocker"}
		}
		{delay 0.3 "errorfuel_reset"
			{for_each_link
				{call "disable_flamer_blocker"}
			}
		}
	}
)

{"ss-d tank"
	{on spawn
		; disable vanilla
		{view stop	"fire1"}
		{view stop	"fire2"}
		{view stop	"fire3"}
		{view stop	"fire4"}
		{view stop	"fire5"}
		{view stop	"flame1"}
		{view stop	"flame2"}
		{view stop	"flame3"}
		{view stop	"flame4"}
		{view stop	"flame5"}
		; add new
		{tags add "flamer"}

		{add_view "flamer_muzzle" "firebarrel" "foresight9"}
		{add_view "flamer_muzzle" "firebarrel" "foresight10"}
		{add_view "flamer_muzzle" "firebarrel" "foresight13"}
		{add_view "flamer_muzzle" "firebarrel" "foresight12"}
		{add_view "flamer_muzzle" "firebarrel" "foresight11"}
        {add_view "flamer_flash" "flashbarrelf1" "foresight9"}
        {add_view "flamer_flash" "flashbarrelf2" "foresight10"}
        {add_view "flamer_flash" "flashbarrelf3" "foresight13"}
        {add_view "flamer_flash" "flashbarrelf4" "foresight12"}
        {add_view "flamer_flash" "flashbarrelf5" "foresight11"}

		{link_sound "flamer_start" "weapon/shot/flame/goh/handheld/flamer_start"}
		{link_sound "flamer_loop" "weapon/shot/flame/goh/handheld/flamer_loop"}
		{link_sound "flamer_stop" "weapon/shot/flame/goh/handheld/flamer_stop"}

        {if operatable
			{view show	"firebarrel"}
			{view start	"firebarrel"}
		else
			{view hide	"firebarrel"}
			{view pause	"firebarrel"}
		}
	}
    {on operatable on
		{view stop	"fire1"}
		{view stop	"fire2"}
		{view stop	"fire3"}
		{view stop	"fire4"}
		{view stop	"fire5"}
		{view show	"firebarrel"}
		{view start	"firebarrel"}
    }
    {on operatable off
		{view stop	"fire1"}
		{view stop	"fire2"}
		{view stop	"fire3"}
		{view stop	"fire4"}
		{view stop	"fire5"}
        {view hide  "firebarrel"}
        {view pause  "firebarrel"}
    }
    ("fuel_checker_light")
    {on break_armor overload
        {if name "blast"
            {if volume "body"
                {if rand 0.5 {kill_crew "gunner"}}
                {if rand 0.5 {kill_crew "charger"}}
                {if rand 0.5 {kill_crew "commander"}}
                {if rand 0.5 {kill_crew "driver"}}
                {if rand 0.5 {kill_crew "gunner2"}}

                {if not tagged "destroyed"
                    {call "mp_destroy"}
                }
            }
            {if volume "explosive"
				{if rand 0.5 {call "explosive_broken"}}
            }
			{if volume "body"
				{call "explosion"}
			}
        }
        {if not user_control
            {if volume "body"
                {if rand 0.1 {kill_crew "gunner"}}
                {if rand 0.1 {kill_crew "charger"}}
                {if rand 0.1 {kill_crew "commander"}}
                {if rand 0.1 {kill_crew "driver"}}
            }
        }
        {if not "no_burn_volumes"
            {if name "pierce"
                {if volume "body"
                    {burn fx "smoke_dead_tank1" fake}
                else volume "track"
                {burn fx "smoke_dead_tank1" fake}
				}
            }
        }
    }
	{on "_explosion" overload
        {view stop  "firebarrel"}
		{view stop	"flashbarrelf1"}
		{view stop	"flashbarrelf2"}
		{view stop	"flashbarrelf3"}
		{view stop	"flashbarrelf4"}
		{view stop	"flashbarrelf5"}
		{view stop	"flamershot1"}
		{view stop	"flamershot2"}
		{view stop	"flamershot3"}
		{view stop	"flamershot4"}
		{view stop	"flamershot5"}
		{view stop	"flamermark1"}
		{view stop	"flamermark2"}
		{view stop	"flamermark3"}
		{view stop	"flamermark4"}
		{view stop	"flamermark5"}
		{spawn "service_balloon_detonator" "body"} ; detonating the fuel tank
		{delay 0.01
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
			; tank
			{add_view "smoke_dead_norm" "deathfx" "FXfire1"}
			{spawn "tank_die" "Basis"}
			; medium tank
			{blastwave c4 10 r0 2.5 r1 10}
			{impulse up 2 0.5 dir 0.4 0.2}
		}
	}
    (define "ssd_fire"
        {on fire "flamer%no" overload
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
			{kill_delay "firef%no"}
            {view show  "flashbarrelf%no"}
            {view start "flashbarrelf%no"}
			{delay 0.4 "firef%no"
				{view hide	"flashbarrelf%no"}
				{view pause	"flashbarrelf%no"}
			}
			{kill_delay "flamershot%no"}
			{if not tagged "flamer_loaded%no"
				{tags add "flamer_loaded%no"}
				{if tagged "napalm_thick"
					{add_view "flamer_marker_napalm_thick" "flamermark%no" "foresight%foresight"}
					{add_view "flamer_fire_napalm_thick" "flamershot%no" "foresight%foresight"}
				else tagged "napalm_thin"
					{add_view "flamer_marker_napalm_thin" "flamermark%no" "foresight%foresight"}
					{add_view "flamer_fire_napalm_thin" "flamershot%no" "foresight%foresight"}
				else tagged "liquid_fuel"
					{add_view "flamer_marker_liquid" "flamermark%no" "foresight%foresight"}
					{add_view "flamer_fire_liquid" "flamershot%no" "foresight%foresight"}
				else
					{add_view "flamer_marker_gas" "flamermark%no" "foresight%foresight"}
					{add_view "flamer_fire_gas" "flamershot%no" "foresight%foresight"}
				}
			}
			{view start	"flamermark%no"}
			{view start	"flamershot%no"}
			{delay 0.1 "flamershot%no"
				{view stop	"flamermark%no"}
				{view stop	"flamershot%no"}
				{tags remove "flamer_loaded%no"}
			}
        }
    )
    ("ssd_fire" no(1) foresight(9))
    ("ssd_fire" no(2) foresight(10))
    ("ssd_fire" no(3) foresight(13))
    ("ssd_fire" no(4) foresight(12))
    ("ssd_fire" no(5) foresight(11))
}
{"churchill_crocodile tank"
	{on spawn
		; disable vanilla
		{view stop	"fire1"}
		{view stop	"flame1"}
		; add new
		{tags add "flamer"}

		{add_view "flamer_muzzle" "firebarrel" "foresight4"}
        {add_view "flamer_flash" "flashbarrelf" "foresight4"}

		{link_sound "flamer_start" "weapon/shot/flame/goh/vehicle/flamer_start"}
		{link_sound "flamer_loop" "weapon/shot/flame/goh/vehicle/flamer_loop"}
		{link_sound "flamer_stop" "weapon/shot/flame/goh/vehicle/flamer_stop"}

        {if operatable
			{view show	"firebarrel"}
			{view start	"firebarrel"}
		else
			{view hide	"firebarrel"}
			{view pause	"firebarrel"}
		}
	}
	{on operatable on
		{view stop	"fire1"}
		{view show	"firebarrel"}
		{view start	"firebarrel"}
	}
	{on operatable off
		{view stop	"fire1"}
		{view hide	"firebarrel"}
		{view pause	"firebarrel"}
	}
    ("fuel_checker_heavy")
    {on break_armor
        {if name "blast"
            {if volume "body"
				{call "explosion"}
			}
		}
    }
	{on "_explosion" overload
        {view stop "firebarrel"}
        {view stop "flashbarrelf"}
        {view stop "flamershot"}
        {view stop "flamermark"}
		{spawn "service_balloon_detonator" "body"} ; detonating the fuel tank
		{delay 0.01
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
			; tank
			{add_view "smoke_dead_norm" "deathfx" "FXfire1"}
			{spawn "tank_die" "Basis"}
			; heavy tank
	        {blastwave c4 15 r0 2.5 r1 10}
			{impulse up 1 1 dir 0.2 0.2}
		}
	}
	{on fire "flamer1" overload
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
		{kill_delay "firef"}
        {view show  "flashbarrelf"}
        {view start "flashbarrelf"}
		{delay 0.4 "firef"
			{view hide	"flashbarrelf"}
			{view pause	"flashbarrelf"}
		}
		{kill_delay "flamershot"}
		{if not tagged "flamer_loaded"
			{tags add "flamer_loaded"}
			{if tagged "napalm_thick"
				{add_view "flamer_marker_napalm_tank" "flamermark" "foresight4"}
				{add_view "flamer_fire_napalm_tank" "flamershot" "foresight4"}
			else
				{add_view "flamer_marker_liquid_tank" "flamermark" "foresight4"}
				{add_view "flamer_fire_liquid_tank" "flamershot" "foresight4"}
			}
		}
		{view start	"flamermark"}
		{view start	"flamershot"}
		{delay 0.1 "flamershot"
			{view stop	"flamermark"}
			{view stop	"flamershot"}
			{tags remove "flamer_loaded"}
		}
	}
}
{"m4a3_zippo tank"
	{on spawn
		; disable vanilla
		{view stop	"fire1"}
		{view stop	"flame1"}
		; add new
		{tags add "flamer"}

        {add_view "flamer_muzzle" "firebarrel" "foresight5"}
		{add_view "flamer_flash" "flashbarrelf" "foresight5"}

		{link_sound "flamer_start" "weapon/shot/flame/goh/vehicle/flamer_start"}
		{link_sound "flamer_loop" "weapon/shot/flame/goh/vehicle/flamer_loop"}
		{link_sound "flamer_stop" "weapon/shot/flame/goh/vehicle/flamer_stop"}

        {if operatable
			{view show	"firebarrel"}
			{view start	"firebarrel"}
		else
			{view hide	"firebarrel"}
			{view pause	"firebarrel"}
		}
	}
	{on operatable on
		{view stop	"fire1"}
		{view show	"firebarrel"}
		{view start	"firebarrel"}
	}
	{on operatable off
		{view stop	"fire1"}
        {view hide  "firebarrel"}
        {view pause "firebarrel"}
	}
    ("fuel_checker_heavy")
    {on break_armor
        {if name "blast"
            {if volume "body"
				{call "explosion"}
			}
		}
    }
	{on "_explosion" overload
        {view stop "firebarrel"}
        {view stop "flashbarrelf"}
        {view stop "flamershot"}
        {view stop "flamermark"}
		{spawn "service_balloon_detonator" "body"} ; detonating the fuel tank
		{delay 0.01
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
			; tank
			{add_view "smoke_dead_norm" "deathfx" "FXfire1"}
			{spawn "tank_die" "Basis"}
			; medium tank
			{blastwave c4 10 r0 2.5 r1 10}
			{impulse up 2 0.5 dir 0.4 0.2}
		}
	}
	{on fire "flamer1" overload
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
		{kill_delay "firef"}
        {view show  "flashbarrelf"}
        {view start "flashbarrelf"}
		{delay 0.4 "firef"
			{view hide	"flashbarrelf"}
			{view pause	"flashbarrelf"}
		}
		{kill_delay "flamershot"}
		{if not tagged "flamer_loaded"
			{tags add "flamer_loaded"}
			{if tagged "napalm_thick"
				{add_view "flamer_marker_napalm_tank" "flamermark" "foresight5"}
				{add_view "flamer_fire_napalm_tank" "flamershot" "foresight5"}
			else
				{add_view "flamer_marker_liquid_tank" "flamermark" "foresight5"}
				{add_view "flamer_fire_liquid_tank" "flamershot" "foresight5"}
			}
		}
		{view start	"flamermark"}
		{view start	"flamershot"}
		{delay 0.1 "flamershot"
			{view stop	"flamermark"}
			{view stop	"flamershot"}
			{tags remove "flamer_loaded"}
		}
	}
}

{"sturmtiger tank"
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
		; tank
		{add_view "smoke_dead_norm" "deathfx" "FXfire1"}
		{spawn "tank_die" "Basis"}
		; heavy tank
        {blastwave c4 15 r0 2.5 r1 10}
		{impulse up 1 1 dir 0.2 0.2}
		; flame
		{if explosive_amount 50
			{spawn "fuel_die"}
			{blastwave c4 5 r0 4 r1 15}
			{fire radius 15 time 0.2 heating 0.2}
			{fire radius 10 time 1 heating 50}
			{fire radius 7.5 time 10 heating 50}
		}
	}
}
{"brummbar tank"
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
		; tank
		{add_view "smoke_dead_norm" "deathfx" "FXfire1"}
		{spawn "tank_die" "Basis"}
		; medium tank
		{blastwave c4 10 r0 2.5 r1 10}
		{impulse up 2 0.5 dir 0.4 0.2}
		; flame
		{if explosive_amount 50
			{spawn "fuel_die"}
			{blastwave c4 5 r0 4 r1 15}
			{fire radius 15 time 0.2 heating 0.2}
			{fire radius 10 time 1 heating 50}
			{fire radius 7.5 time 10 heating 50}
		}
	}
}

{"ha-to"
	{on crew in
		{if crew_in_place "driver"
			{with_linked_entity "driver"
				{tags add "in_hatch"}
			}
		}
		{if crew_in_place "commander"
			{with_linked_entity "commander"
				{tags add "in_hatch"}
			}
		}
	}
}

{"armored_car"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
}
{"light tank"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
}
{"marder_3h"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
}
{"wespe"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
}
{"wespe_ger2"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
}
{"m19"
	{on spawn
		{delay 0.01
			{tags add "classify_as_light"}
		}
	}
}