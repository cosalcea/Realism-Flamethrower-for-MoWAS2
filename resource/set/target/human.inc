{selector
	{unit "human"}

	{group
		{sort {in_range 5}}
		{sort {attacking} {weapon "flame_thrower"}}
		{sort {attacking}}
		{sort {class human} {weapon "flame_thrower showy"}}
		{sort {class human} {weapon "bullet"}}
		{sort {class human} {weapon}}
		{sort {class tank}}
		{sort {class armoredcar}}
		{sort {weapon}}
		{sort {class human}}
		{sort distance}
	}
	{group
		{sort distance}
	}
}