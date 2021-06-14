	{any
		{translate_damage 7}		; damage modifier for blastwave

		{cover_hitchance 0.5}   	; the probability of hitting a soldier behind cover
		{crawl_hitchance 0.5}  		; the probabiltiy of hitting a soldier in crawl position
		{cover_damage 0.5}  		; damage when protected by cover
		; ↑ Applying to these 3 parameters
		{cover_efficiency			; how cover & crawl efficiency will drop with distance
			0	0
			10	0.15
			30	0.75
			50	1.00
		 ;distance   efficiency, higher = better
		}

		{vehicle_burst 2}			; increase bullet count in 1 burst for all vehicles
		{cover_mgun_burst 2}		; increase bullet count in 1 burst of soldier with mgun in horizontal cover
		{cover_mgun_delay 0}		; decrease timeout between bursts of soldier with mgun in horizontal cover

		{blast_crawl 1.25}			; simply lying on the ground
		{blast_cover 1.50}          ; in cover from protected side
		{blast_crawl_prepared 1.75}	; lying on the ground & waiting for explosion
		{blast_cover_prepared 2.00}	; in cover not from protected side, but waiting for explosion
		{blast_squat 1.15}			; on the knees

		{death_delay_min 30}		; min bleeding out time in seconds
		{death_delay_max 90}		; max bleeding out time in seconds
	}