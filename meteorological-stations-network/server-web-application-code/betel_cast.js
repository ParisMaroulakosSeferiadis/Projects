// beteljuice.com - near enough Zambretti Algorhithm 
// June 2008 - v1.0
// tweak added so decision # can be output

/* Negretti and Zambras 'slide rule' is supposed to be better than 90% accurate 
for a local forecast upto 12 hrs, it is most accurate in the temperate zones and about 09:00  hrs local solar time.
I hope I have been able to 'tweak it' a little better ;-)	

This code is free to use and redistribute as long as NO CHARGE is EVER made for its use or output
*/

// ---- 'environment' variables ------------
var z_where = 1;  // Northern = 1 or Southern = 2 hemisphere
var z_baro_top = 1050;	// upper limits of your local 'weather window' (1050.0 hPa for UK)
var z_baro_bottom = 950;	// lower limits of your local 'weather window' (950.0 hPa for UK)

// usage:   forecast = betel_cast( z_hpa, z_month, z_wind, z_trend [, z_where] [, z_baro_top] [, z_baro_bottom])[0];

// z_hpa is Sea Level Adjusted (Relative) barometer in hPa or mB
// z_month is current month as a number between 1 to 12
// z_wind is English windrose cardinal eg. N, NNW, NW etc.
// NB. if calm a 'nonsense' value should be sent as z_wind (direction) eg. 1 or calm !
// z_trend is barometer trend: 0 = no change, 1= rise, 2 = fall
// z_where - OPTIONAL for posting with form
// z_baro_top - OPTIONAL for posting with form
// z_baro_bottom - OPTIONAL for posting with form
// [0] a short forecast text is returned
// [1] zambretti severity number (0 - 25) is returned ie. betel_cast() returns a two deep array


var z_forecast = new Array("Settled fine", "Fine weather", "Becoming fine", "Fine, becoming less settled", "Fine, possible showers", "Fairly fine, improving", "Fairly fine, possible showers early", "Fairly fine, showery later", "Showery early, improving", "Changeable, mending", "Fairly fine, showers likely", "Rather unsettled clearing later", "Unsettled, probably improving", "Showery, bright intervals", "Showery, becoming less settled", "Changeable, some rain", "Unsettled, short fine intervals", "Unsettled, rain later", "Unsettled, some rain", "Mostly very unsettled", "Occasional rain, worsening", "Rain at times, very unsettled", "Rain at frequent intervals", "Rain, very unsettled", "Stormy, may improve", "Stormy, much rain"); 

// equivalents of Zambretti 'dial window' letters A - Z
var rise_options  = new Array(25,25,25,24,24,19,16,12,11,9,8,6,5,2,1,1,0,0,0,0,0,0) ; 
var steady_options  = new Array(25,25,25,25,25,25,23,23,22,18,15,13,10,4,1,1,0,0,0,0,0,0) ; 
var fall_options =  new Array(25,25,25,25,25,25,25,25,23,23,21,20,17,14,7,3,1,1,1,0,0,0) ; 

var z_test = new Array();

// ---- MAIN FUNCTION --------------------------------------------------
function betel_cast( z_hpa, z_month, z_wind, z_trend, z_hemisphere, z_upper, z_lower) {
	if(z_hemisphere) z_where = z_hemisphere;	// used by input form
	if(z_upper) z_baro_top = z_upper;	// used by input form
	if(z_lower) z_baro_bottom = z_lower; 	// used by input form
	z_range = z_baro_top - z_baro_bottom;
	z_constant = (z_range / 22).toFixed(3);

	z_season = (z_month >= 4 && z_month <= 9) ; 	// true if 'Summer'
	if (z_where == 1) {  		// North hemisphere
		if (z_wind == "N") {  
			z_hpa += 6 / 100 * z_range ;  
		} else if (z_wind == "NNE") {  
			z_hpa += 5 / 100 * z_range ;  
		} else if (z_wind == "NE") {  
//			z_hpa += 4 ;  
			z_hpa += 5 / 100 * z_range ;  
		} else if (z_wind == "ENE") {  
			z_hpa += 2 / 100 * z_range ;  
		} else if (z_wind == "E") {  
			z_hpa -= 0.5 / 100 * z_range ;  
		} else if (z_wind == "ESE") {  
//			z_hpa -= 3 ;  
			z_hpa -= 2 / 100 * z_range ;  
		} else if (z_wind == "SE") {  
			z_hpa -= 5 / 100 * z_range ;  
		} else if (z_wind == "SSE") {  
			z_hpa -= 8.5 / 100 * z_range ;  
		} else if (z_wind == "S") {  
//			z_hpa -= 11 ;  
			z_hpa -= 12 / 100 * z_range ;  
		} else if (z_wind == "SSW") {  
			z_hpa -= 10 / 100 * z_range ;  //
		} else if (z_wind == "SW") {  
			z_hpa -= 6 / 100 * z_range ;  
		} else if (z_wind == "WSW") {  
			z_hpa -= 4.5 / 100 * z_range ;  //
		} else if (z_wind == "W") {  
			z_hpa -= 3 / 100 * z_range ;  
		} else if (z_wind == "WNW") {  
			z_hpa -= 0.5 / 100 * z_range ;  
		}else if (z_wind == "NW") {  
			z_hpa += 1.5 / 100 * z_range ;  
		} else if (z_wind == "NNW") {  
			z_hpa += 3 / 100 * z_range ;  
		} 
		if (z_season == 1) {  	// if Summer
			if (z_trend == 1) {  	// rising
				z_hpa += 7 / 100 * z_range;  
			} else if (z_trend == 2) {  //	falling
				z_hpa -= 7 / 100 * z_range; 
			} 
		} 
	} else {  	// must be South hemisphere
		if (z_wind == "S") {  
			z_hpa += 6 / 100 * z_range ;  
		} else if (z_wind == "SSW") {  
			z_hpa += 5 / 100 * z_range ;  
		} else if (z_wind == "SW") {  
//			z_hpa += 4 ;  
			z_hpa += 5 / 100 * z_range ;  
		} else if (z_wind == "WSW") {  
			z_hpa += 2 / 100 * z_range ;  
		} else if (z_wind == "W") {  
			z_hpa -= 0.5 / 100 * z_range ;  
		} else if (z_wind == "WNW") {  
//			z_hpa -= 3 ;  
			z_hpa -= 2 / 100 * z_range ;  
		} else if (z_wind == "NW") {  
			z_hpa -= 5 / 100 * z_range ;  
		} else if (z_wind == "NNW") {  
			z_hpa -= 8.5 / 100 * z_range ;  
		} else if (z_wind == "N") {  
//			z_hpa -= 11 ;  
			z_hpa -= 12 / 100 * z_range ;  
		} else if (z_wind == "NNE") {  
			z_hpa -= 10 / 100 * z_range ;  //
		} else if (z_wind == "NE") {  
			z_hpa -= 6 / 100 * z_range ;  
		} else if (z_wind == "ENE") {  
			z_hpa -= 4.5 / 100 * z_range ;  //
		} else if (z_wind == "E") {  
			z_hpa -= 3 / 100 * z_range ;  
		} else if (z_wind == "ESE") {  
			z_hpa -= 0.5 / 100 * z_range ;  
		}else if (z_wind == "SE") {  
			z_hpa += 1.5 / 100 * z_range ;  
		} else if (z_wind == "SSE") {  
			z_hpa += 3 / 100 * z_range ;  
		} 
		if (z_season == 0) { 	// if Winter
			if (z_trend == 1) {  // rising
				z_hpa += 7 / 100 * z_range;  
			} else if (z_trend == 2) {  // falling
				z_hpa -= 7 / 100 * z_range; 
			} 
		} 
	} 	// END North / South

	if(z_hpa == z_baro_top) z_hpa = z_baro_top - 1;
	z_option = Math.floor((z_hpa - z_baro_bottom) / z_constant); 
 	z_output = "";
	if(z_option < 0) {
		z_option = 0;
		z_output = "Exceptional Weather, ";
	}
	if(z_option > 21) {
		z_option = 21;
		z_output = "Exceptional Weather, ";
	}

	if (z_trend == 1) { 	// rising
		z_output += z_forecast[rise_options[z_option]] ; 
z_test[1] = rise_options[z_option];
	} else if (z_trend == 2) { 	// falling
		z_output += z_forecast[fall_options[z_option]] ; 
z_test[1] = fall_options[z_option];
	} else { 	// must be 'steady'
		z_output += z_forecast[steady_options[z_option]] ; 
z_test[1] = steady_options[z_option];
	} 
//	return z_output ; 
z_test[0] = z_output ;
return z_test ; 
}	// END function   		
		
