(include "vehicle_selected.inc" name("selection_active") scale(%scale) )
(include "vehicle_selected.inc" name("selection_selected") scale(%scale) )

(define "shoot_blocker_shock_link"
	{place "shoot_blocker_shock%0"
		{entity "service_shoot_blocker_shock"}
		{linkbone "foresight%0"}
	}
)
{placer
	("shoot_blocker_shock_link" args 1)
	("shoot_blocker_shock_link" args 2)
	("shoot_blocker_shock_link" args 3)
	("shoot_blocker_shock_link" args 4)
	("shoot_blocker_shock_link" args 5)
	("shoot_blocker_shock_link" args 6)
	("shoot_blocker_shock_link" args 7)
	("shoot_blocker_shock_link" args 8)
	("shoot_blocker_shock_link" args 9)
	("shoot_blocker_shock_link" args 10)
	("shoot_blocker_shock_link" args 11)
	("shoot_blocker_shock_link" args 12)
	("shoot_blocker_shock_link" args 13)
	("shoot_blocker_shock_link" args 14)
	("shoot_blocker_shock_link" args 15)
}