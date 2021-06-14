{"grenade"
	{on "onThrow" overload
		{volumes "body" disable contact overlap}
		{delay 0.1
			{tags add "fused"}
			{volumes "body" enable contact overlap}
		}
	}
	{on "onThrowActivate" overload}
	{on contact overload}
	{on "in_hole" overload
		{if not tagged "in_hole"
			{tags add "in_hole"}
			{delay_ex 0.1
				{tags remove "in_hole"}
			}
		}
	}
	{on ground_hit
		{if tagged "fused"
			{delay 0.2
				{if not velocity 3
					{fall_down}
				}
			}
		}
	}
	{on "fall_down" overload}
	; The "{fall_down}" needs an extra "impulse" to push the grenade, causes it falling to ground slowly.
	; Without "impulse" (vanilla mistake) it will keep the grenade stuck in the air.
}
{"grenade contact"
	{on ground_hit overload
		{if tagged "fused"
			{if not name "water"
				{call "ground_detonate"}
			}
		}
	}
	{on "in_hole" overload
		{if not tagged "in_hole"
			{tags add "in_hole"}
			{delay_ex 0.1
				{tags remove "in_hole"}
			}
		}
	}
	{on contact overload
		{if effector "vehicle"
			{if tagged "fused"
				{call "contact_detonate"}
			}
		else effector "human"
			{if tagged "fused"
				{call "contact_detonate"}
			}
		else
			{delay_ex 0
				{if not tagged "in_hole"
					{if tagged "fused"
						{call "contact_detonate"}
					}
				}
			}
		}
	}
	{on overlap begin overload
		{if not effector "vehicle"
			{if not effector "human"
				{if not effector "tree"
					{if not effector "bush"
						{delay_ex 0
							{if not tagged "in_hole"
								{if tagged "fused"
									{call "contact_detonate"}
								}
							}
						}
					}
				}
			}
		}
	}
	{on "detonate" overload
		{if not tagged "detonated"
			{tags add "detonated"}
			{stuff_detonate}
		}
	}
}