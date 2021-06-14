{"construction"
	{on spawn
		{delay 0.01
			; fix the vanilla bug
			{volumes "smoke0" disable all}
			{volumes "smoke1" disable all}
			{volumes "smoke2" disable all}
			{volumes "smoke3" disable all}
			{volumes "smoke4" disable all}
			{volumes "smoke5" disable all}
			{volumes "hole0" disable all}
			{volumes "hole1" disable all}
			{volumes "hole2" disable all}
			{volumes "hole3" disable all}
			{volumes "hole4" disable all}
			{volumes "hole5" disable all}
			{volumes "hole6" disable all}
			{volumes "hole7" disable all}
			{volumes "hole8" disable all}
			{volumes "hole9" disable all}
			{volumes "hole10" disable all}
			{volumes "hole11" disable all}
			{volumes "hole12" disable all}
			{volumes "hole13" disable all}
			{volumes "hole14" disable all}
			{volumes "hole15" disable all}
			{volumes "hole16" disable all}
			{volumes "hole17" disable all}
			{volumes "hole18" disable all}
			{volumes "hole19" disable all}
			{volumes "hole20" disable all}
			{volumes "hole21" disable all}
			{volumes "hole22" disable all}
			{volumes "hole23" disable all}
			{volumes "hole0" enable hole touch}
			{volumes "hole1" enable hole touch}
			{volumes "hole2" enable hole touch}
			{volumes "hole3" enable hole touch}
			{volumes "hole4" enable hole touch}
			{volumes "hole5" enable hole touch}
			{volumes "hole6" enable hole touch}
			{volumes "hole7" enable hole touch}
			{volumes "hole8" enable hole touch}
			{volumes "hole9" enable hole touch}
			{volumes "hole10" enable hole touch}
			{volumes "hole11" enable hole touch}
			{volumes "hole12" enable hole touch}
			{volumes "hole13" enable hole touch}
			{volumes "hole14" enable hole touch}
			{volumes "hole15" enable hole touch}
			{volumes "hole16" enable hole touch}
			{volumes "hole17" enable hole touch}
			{volumes "hole18" enable hole touch}
			{volumes "hole19" enable hole touch}
			{volumes "hole20" enable hole touch}
			{volumes "hole21" enable hole touch}
			{volumes "hole22" enable hole touch}
			{volumes "hole23" enable hole touch}
			{volumes "window0" enable hole}
			{volumes "window1" enable hole}
			{volumes "window2" enable hole}
			{volumes "window3" enable hole}
			{volumes "window4" enable hole}
			{volumes "window5" enable hole}
			{volumes "window6" enable hole}
			{volumes "window7" enable hole}
			{volumes "window8" enable hole}
			{volumes "window9" enable hole}
			{volumes "window10" enable hole}
			{volumes "window11" enable hole}
			{volumes "window12" enable hole}
			{volumes "window13" enable hole}
			{volumes "window14" enable hole}
			{volumes "window15" enable hole}
			{volumes "window16" enable hole}
			{volumes "window17" enable hole}
			{volumes "window18" enable hole}
			{volumes "window19" enable hole}
			{volumes "window20" enable hole}
			{volumes "window21" enable hole}
			{volumes "window22" enable hole}
			{volumes "window23" enable hole}
		}
	}
}

{"straw construction"
	{inflammation_time 30}
	{on contact
		{if effector "flamer_marker"
			{burn volume fx "smoke_dead_small" time 6 1 fake even_law}
			{start_sound "weapon/shot/flame/fire"}
		}
	}
	{on blast_hit
		{if stuff "molotov_coctail"
			{if not volume "window0"
			{if not volume "window1"
			{if not volume "window2"
			{if not volume "window3"
			{if not volume "window4"
			{if not volume "window5"
			{if not volume "window6"
			{if not volume "window7"
			{if not volume "window8"
			{if not volume "window9"
			{if not volume "window10"
			{if not volume "window11"
			{if not volume "window12"
			{if not volume "window13"
			{if not volume "window14"
			{if not volume "window15"
			{if not volume "window16"
			{if not volume "window17"
			{if not volume "window18"
			{if not volume "window19"
			{if not volume "window20"
			{if not volume "window21"
			{if not volume "window22"
			{if not volume "window23"
				{burn fx "smoke_dead_small1" time 10 fake even_law}
				{start_sound "weapon/shot/flame/fire"}
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
		}
	}
}
{"wood construction"
	{inflammation_time 100}
	{on contact
		{if effector "flamer_marker"
			{burn volume fx "smoke_dead_small" time 6 1 fake even_law}
			{start_sound "weapon/shot/flame/fire"}
		}
	}
	{on blast_hit
		{if stuff "molotov_coctail"
			{if not volume "window0"
			{if not volume "window1"
			{if not volume "window2"
			{if not volume "window3"
			{if not volume "window4"
			{if not volume "window5"
			{if not volume "window6"
			{if not volume "window7"
			{if not volume "window8"
			{if not volume "window9"
			{if not volume "window10"
			{if not volume "window11"
			{if not volume "window12"
			{if not volume "window13"
			{if not volume "window14"
			{if not volume "window15"
			{if not volume "window16"
			{if not volume "window17"
			{if not volume "window18"
			{if not volume "window19"
			{if not volume "window20"
			{if not volume "window21"
			{if not volume "window22"
			{if not volume "window23"
				{burn fx "smoke_dead_small1" time 10 fake even_law}
				{start_sound "weapon/shot/flame/fire"}
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
		}
	}
}
{"concrete construction"
	{inflammation_time 200}
	{on contact
		{if effector "flamer_marker"
			{burn volume fx "smoke_dead_small" time 3 1 fake even_law}
			{start_sound "weapon/shot/flame/fire"}
		}
	}
	{on blast_hit
		{if stuff "molotov_coctail"
			{if not volume "window0"
			{if not volume "window1"
			{if not volume "window2"
			{if not volume "window3"
			{if not volume "window4"
			{if not volume "window5"
			{if not volume "window6"
			{if not volume "window7"
			{if not volume "window8"
			{if not volume "window9"
			{if not volume "window10"
			{if not volume "window11"
			{if not volume "window12"
			{if not volume "window13"
			{if not volume "window14"
			{if not volume "window15"
			{if not volume "window16"
			{if not volume "window17"
			{if not volume "window18"
			{if not volume "window19"
			{if not volume "window20"
			{if not volume "window21"
			{if not volume "window22"
			{if not volume "window23"
				{burn fx "smoke_dead_small1" time 10 fake even_law}
				{start_sound "weapon/shot/flame/fire"}
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
		}
	}
}
{"burning_old construction"
	(define "burn_volume_rf"
		{delay %1 0.7
			{if not "stop_burn"
				{start_sound "weapon/shot/flame/fire"}
				{burn volume "fire%0" fx "smoke_fire_window" time 20 fake even_law}
				{fire volume "fire%0" radius 1 time 20 heating 3}
				{burn volume "smoke%0" fx "smoke_black_window" time 20 fake even_law}
				{fire volume "smoke%0" radius 1 time 20 heating 3}
			}
		}
	)
	(define "burn_from_volume_rf"
		{if not burned
			{if volume %0
				("burn_volume_rf" args %1 %2)
				("burn_volume_rf" args %3 %4)
				("burn_volume_rf" args %5 %6)
				("burn_volume_rf" args %7 %8)
				("burn_volume_rf" args %9 %10)
				("burn_volume_rf" args %11 %12)
				("burn_volume_rf" args %13 %14)
				("burn_volume_rf" args %15 %16)
				("burn_volume_rf" args %17 %18)
				{burn time 60}
				{delay 20 3
					{call "next_stage"}
	 				{call "burn_end"}
				}
			}
		}
	)
	{on "burn_process" overload
		{if not "last_stage"
			("burn_from_volume_rf" args "fire0"	0 2		1 4		2 8		3 12	4 16	5 18	6 16	7 12	8 8		9 4)
			("burn_from_volume_rf" args "fire1"	1 2		2 4		3 8		4 12	5 16	6 18	7 16	8 12	9 8		0 4)
			("burn_from_volume_rf" args "fire2"	2 2		3 4		4 8		5 12	6 16	7 18	8 16	9 12	0 8		1 4)
			("burn_from_volume_rf" args "fire3"	3 2		4 4		5 8		6 12	7 16	8 18	9 16	0 12	1 8		2 4)
			("burn_from_volume_rf" args "fire4"	4 2		5 4		6 8		7 12	8 16	9 18	0 16	1 12	2 8		3 4)
			("burn_from_volume_rf" args "fire5"	5 2		6 4		7 8		8 12	9 16	0 18	1 16	2 12	3 8		4 4)
			("burn_from_volume_rf" args "fire6"	6 2		7 4		8 8		9 12	0 16	1 18	2 16	3 12	4 8		5 4)
			("burn_from_volume_rf" args "fire7"	7 2		8 4		9 8		0 12	1 16	2 18	3 16	4 12	5 8		6 4)
			("burn_from_volume_rf" args "fire8"	8 2		9 4		0 8		1 12	2 16	3 18	4 16	5 12	6 8		7 4)
			("burn_from_volume_rf" args "fire9"	9 2		0 4		1 8		2 12	3 16	4 18	5 16	6 12	7 8		8 4)
			("burn_from_volume_rf" args "body"		1 2		2 4		3 8		4 12	5 16	6 18	7 16	8 12	9 8		0 4)
			("burn_from_volume_rf" args "body1"	2 2		3 4		4 8		5 12	6 16	7 18	8 16	9 12	0 8		1 4)
		}
	}
	{on "burn_body" overload
		{if volume "fire"
			{if not burned
				{if not "last_stage"
					{start_sound "weapon/shot/flame/fire"}
					{burn volume fx "smoke_dead_tree1" time 20 fake even_law}
					{fire radius 1 time 20 heating 3}
					{burn time 20}
					{delay 20
						{call "next_stage"}
		 				{call "burn_end"}
					}
				}
			}
		else
			{call "burn_process"}
		}
	}
}
{"burning construction"
	(define "burn_volume_fx_rf"
		{start_sound "weapon/shot/flame/fire"}
		{burn volume fx %0 time 20 fake even_law}
		{fire radius 1 time 20 heating 3}
	)
	(define "burn_bone_fx_rf"
		{start_sound "weapon/shot/flame/fire"}
		{burn fx %0 time 20 fake even_law}
		{fire radius 1 time 20 heating 3}
	)
	{on "burn_volume_next" overload
		{if volume "window"
			{if volume "fire"
				("burn_bone_fx_rf" args "smoke_fire_window")
			else volume "smoke"
				("burn_bone_fx_rf" args "smoke_black_window")
			}
		else
			{if volume "fire"
				("burn_volume_fx_rf" args "smoke_fire_window")
			else volume "smoke"
				("burn_volume_fx_rf" args "smoke_fire_window")
			}
		}
	}
}