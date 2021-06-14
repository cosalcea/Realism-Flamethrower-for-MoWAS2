{"cannon"
	{inflammation_time 0.1}
	{on spawn
		{delay 0.01
			{tags add "artillery"}
		}
	}

	{on "burn_volume"
		{if tagged "ignited" ; Flamethrower
            {if volume "turret"
				("burn_body" p(0.05))
			}
		}
		{if tagged "ignited_thick" ; Thickened fuel extra dice
            {if volume "turret"
				("burn_body" p(0.025))
			}
		}
		{if tagged "ignited_molotov" ; Molotov
            {if volume "turret"
				("burn_body" p(0.10))
			}
		}
	}

	{on break
		{if component "gun"
			{call "update_gun"}
            {tags add "gun_brake"}
		}
	}
	{on repair
		{if component "gun"
			{call "update_gun"}
            {tags remove "gun_brake"}
		}
	}
	{on "update_gun"
		{if work "gun"
			{weapon_work "gun" 1}
		 else
			{weapon_work "gun" 0}
		}
	}
}