; == STANDARD ==
(define "standard_competitive"
	{common
		{unitset
			{value "all^arcade"}
		}
		{commandPoints "*=%cp"}
		{unitLimits "flamer=3;sniper_only=2;officer=1;heavyaa=1;single=20"}
		{balancingFactorBonus {cp 1.0} {mp 1.0} }
		{chargeFactors
			{value "*=1"}
		}
		{budgets
			{vehicle
				{mode "standard"}
				{resource
					{start 		%start}
					{finish 	%finish}
					{growTime	1500}		; in seconds
					{growTable 	"0.65 0.65 0.65 0.70 0.70 0.70 0.75 0.75 0.75 0.80 0.80 0.80 0.80 0.80 0.80 0.85 0.85 0.85 0.90 0.90 0.90 0.90 0.90 0.90 1.00"}
					{payback
						{cp 		"0		25		50 		60		70		80		90"}
						{restore 	"1.50	1.25	0.75	0.50	0.40	0.30	0.20"}
					}
				}
				{buttons "squad1 squad2 v1 v2 v3 v4 v5"}
			}
			{hero
				{resource
					{start 		10}
				}
				{buttons "hero"}
				{tag "special"}
			}
		}
	}
	{bots
		(include "bots_generic.inc")
	}
)


; == CUSTOM ==
(define "custom_competitive"
	{common
		{unitset
			{value "all^arcade"}
		}
		{commandPoints "*=%cp"}
		{unitLimits "flamer=3;sniper_only=2;officer=1;heavyaa=1;single=20"}
		{balancingFactorBonus {cp 1.0} {mp 1.0} }
		{chargeFactors
			{value "*=1"}
		}
		{budgets
			{vehicle
				{mode "custom"}
				{resource
					{start 		%start}
					{finish 	%finish}
					{growTime	1500}		; in seconds
					{growTable 	"0.65 0.65 0.65 0.70 0.70 0.70 0.75 0.75 0.75 0.80 0.80 0.80 0.80 0.80 0.80 0.85 0.85 0.85 0.90 0.90 0.90 0.90 0.90 0.90 1.00"}
					{payback
						{cp 		"0		25		50 		60		70		80		90"}
						{restore 	"1.50	1.25	0.75	0.50	0.40	0.30	0.20"}
					}
					{limitmin	1000}
					{limitmax	50000}
					{speedset 	"2500 3000 3500 4000 4500 5000 8000 10000 20000 50000"}
				}
				{buttons "squad1 squad2 v1 v2 v3 v4 v5"}
			}
			{hero
				{resource
					{start 		10}
				}
				{buttons "hero"}
				{tag "special"}
			}
		}
	}
	{bots
		(include "bots_generic.inc")
	}
)


;------------------------------------------------------------------------------------------------------------
{presets
	{"s:standard_100_competitive_fnl"
		{gameMode "standard"}
		{unitMode "competitive_fnl"}
		{specMode "competitive_normal"}
		("standard_competitive" 		start(160) finish(3000) cp(100))
		{ranked}

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"s:standard_160_competitive_fnl"
		{gameMode "standard"}
		{unitMode "competitive_fnl"}
		{specMode "competitive_high"}
		("standard_competitive" 		start(600) finish(4000) cp(140))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"s:standard_100_competitive"
		{gameMode "standard"}
		{unitMode "competitive"}
		{specMode "competitive_normal"}
		("standard_competitive" 		start(160) finish(3000) cp(100))
		{ranked}

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"s:standard_160_competitive"
		{gameMode "standard"}
		{unitMode "competitive"}
		{specMode "competitive_high"}
		("standard_competitive" 		start(600) finish(4000) cp(140))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}

;------------------------------------------------------------------------------------------------------------
	{"c:custom_50_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_50"}
		("custom_competitive" 			start(160) finish(3000) cp(50))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_60_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_60"}
		("custom_competitive" 			start(160) finish(3000) cp(60))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_80_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_80"}
		("custom_competitive" 			start(160) finish(3000) cp(80))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_100_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_100"}
		("custom_competitive" 			start(160) finish(3000) cp(100))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_120_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_120"}
		("custom_competitive"  			start(160) finish(3000) cp(120))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_140_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_140"}
		("custom_competitive"  			start(160) finish(3000) cp(140))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_160_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_160"}
		("custom_competitive"  			start(160) finish(3000) cp(160))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_180_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_180"}
		("custom_competitive"  			start(160) finish(3000) cp(180))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}
	{"c:custom_200_competitive_fnl"
		{gameMode "custom"}
		{unitMode "competitive_fnl"}
		{specMode "cp_200"}
		("custom_competitive"  			start(160) finish(3000) cp(200))

		{common
			{unitset
				{value "all^arcade|flamer_limit"}
			}
			{unitLimits "sniper_only=2;officer=1;heavyaa=1;single=20"}
		}
	}

	{"c:custom_50_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_50"}
		("custom_competitive" 			start(160) finish(3000) cp(50))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_60_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_60"}
		("custom_competitive" 			start(160) finish(3000) cp(60))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_80_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_80"}
		("custom_competitive" 			start(160) finish(3000) cp(80))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_100_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_100"}
		("custom_competitive" 			start(160) finish(3000) cp(100))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_120_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_120"}
		("custom_competitive"  			start(160) finish(3000) cp(120))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_140_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_140"}
		("custom_competitive"  			start(160) finish(3000) cp(140))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_160_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_160"}
		("custom_competitive"  			start(160) finish(3000) cp(160))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_180_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_180"}
		("custom_competitive"  			start(160) finish(3000) cp(180))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
	{"c:custom_200_competitive"
		{gameMode "custom"}
		{unitMode "competitive"}
		{specMode "cp_200"}
		("custom_competitive"  			start(160) finish(3000) cp(200))

		{common
			{unitset
				{value "all^arcade|flamer_no_limit"}
			}
		}
	}
;------------------------------------------------------------------------------------------------------------
}