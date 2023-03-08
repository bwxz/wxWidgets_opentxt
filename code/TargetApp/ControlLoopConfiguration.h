#ifndef CONTROL_LOOP_CONFIGURATION_H
#define CONTROL_LOOP_CONFIGURATION_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************/
/*  default network PLL parameters  */
/************************************/
/*The PLL bandwidth values are calculated from the individual 
gains and filter bandwidths	using MathCad. 
If any of these is changed, the PLL bandwidths must be recalculated.  */

#define NETWORK_UNLOCKED_PLL_BANDWIDTH				10.0E-3
#define NETWORK_LOCKED_PLL_BANDWIDTH				1.0E-3
#define INITIAL_NETWORK_UNLOCKED_PLL_BANDWIDTH		NETWORK_UNLOCKED_PLL_BANDWIDTH		//the unlocked bandwidth during initial period
#define INITIAL_NETWORK_LOCKED_PLL_BANDWIDTH		8.0e-3		//the locked bandwidth during initial period
#define END_TICK_FOR_INITIAL_WIDE_PLL_BANDWIDTH		(180*SLOW_TICKS_PER_SECOND)
#define END_TICK_FOR_SECONDARY_WIDE_PLL_BANDWIDTH	(300*SLOW_TICKS_PER_SECOND)
#define SKIP_SMALL_DELAY_JUMP_CHECK_AFTER_CAL_B		(90*SLOW_TICKS_PER_SECOND)

#define NOISE_FOR_MINIMUM_PLL_BANDWIDTH_OCXO		6.0e-8f			//above this noise level, noise-based PLL bandwidth will stay the minimum
#define NOISE_FOR_MAXIMUM_PLL_BANDWIDTH_OCXO		2.5e-8f			//below this noise level, noise-based PLL bandwidth will change toward to maximum
#define NOISE_FOR_MINIMUM_PLL_BANDWIDTH_TCXO		8.0e-8f			//above this noise level, noise-based PLL bandwidth will stay the minimum
#define NOISE_FOR_MAXIMUM_PLL_BANDWIDTH_TCXO		3.5e-8f			//below this noise level, noise-based PLL bandwidth will change toward to maximum
#define RTD_BASED_MINIMUM_PLL_BANDWIDTH				2.0e-3f

#define HYBRID_NOISE_FOR_MINIMUM_PLL_BANDWIDTH_OCXO		4.5e-8f			//above this noise level, noise-based PLL bandwidth will stay the minimum
#define HYBRID_NOISE_FOR_MAXIMUM_PLL_BANDWIDTH_OCXO		2.5e-8f			//below this noise level, noise-based PLL bandwidth will change toward to maximum

#define PERIOD_FOR_INCREASED_INCREASING_STEP		(10*60*SLOW_TICKS_PER_SECOND)	//The period when there is continuous b/w increase and the increase step is increased
#define NOISE_BASED_PLL_BANDWIDTH_MAXIMUM_STEP		1.0e-5f			//The maximum speed is 2.4mHz per minutes
#define NOISE_BASED_PLL_BANDWIDTH_INCREASE_STEP		1.0e-6f			//it sets the maximum noise-based PLL bandwidth increasing speed as 7.2mHz per half hour
#define HYBRID_NOISE_BASED_PLL_BANDWIDTH_INCREASE_STEP		1.0e-6f			//it sets the maximum noise-based PLL bandwidth increasing speed as 7.2mHz per half hour
#define BC_NOISE_BASED_PLL_BANDWIDTH_INCREASE_STEP	1.0e-6f			//it sets the maximum noise-based PLL bandwidth increasing speed as 7.2mHz per 0.5hour under BC mode
#define RTD_BASED_PLL_BANDWIDTH_INCREASE_STEP		8.33e-6f			//increase speed at 2.00mHz per minutes

#define NETWORK_UNLOCKED_PLL_FILTER_BANDWIDTH		0.1f
#define NETWORK_UNLOCKED_PROPORTIONAL_GAIN			0.025f  
#define NETWORK_UNLOCKED_INTEGRAL_GAIN				150e-6f 

#define NETWORK_LOCKED_PLL_FILTER_BANDWIDTH			0.005f
#define NETWORK_LOCKED_PROPORTIONAL_GAIN			0.00125f 
#define NETWORK_LOCKED_INTEGRAL_GAIN				0.30e-6f 

#define NETWORK_FILTER_CHAIN_LENGTH					2


/**********************************/
/*  default wired PLL parameters  */
/**********************************/

/*The PLL bandwidth values are calculated from the individual 
gains and filter bandwidths	using MathCad. 
If any of these is changed, the PLL bandwidths must be recalculated.  */
#define CLOCK_UNLOCKED_PLL_BANDWIDTH				137.733E-3
#define CLOCK_LOCKED_PLL_BANDWIDTH					CLOCK_UNLOCKED_PLL_BANDWIDTH

#define CLOCK_UNLOCKED_FILTER_BANDWIDTH				0.75 	/**< Default unlocked bandwidth for 1PPS locking */
#define CLOCK_UNLOCKED_PROPORTIONAL_GAIN			0.5f
#define CLOCK_UNLOCKED_INTEGRAL_GAIN				10e-3f


#define CLOCK_LOCKED_FILTER_BANDWIDTH				CLOCK_UNLOCKED_FILTER_BANDWIDTH		/**< Default locked bandwidth for 1PPS locking */
#define CLOCK_LOCKED_PROPORTIONAL_GAIN				CLOCK_UNLOCKED_PROPORTIONAL_GAIN
#define CLOCK_LOCKED_INTEGRAL_GAIN					CLOCK_UNLOCKED_INTEGRAL_GAIN

#define CLOCK_FILTER_CHAIN_LENGTH					1 


/****************************************************************/
/*  default time smoother mode PLL parameters                   */
/****************************************************************/
#define TIME_SMOOTHER_UNLOCKED_PLL_BANDWIDTH		(NETWORK_UNLOCKED_PLL_BANDWIDTH)
#define TIME_SMOOTHER_LOCKED_PLL_BANDWIDTH			(NETWORK_LOCKED_PLL_BANDWIDTH * 0.25)


/****************************************************************/
/*  default syntonised/unsyntonised hybrid mode PLL parameters - */
/****************************************************************/
#define HYBRID_UNLOCKED_PLL_BANDWIDTH				NETWORK_UNLOCKED_PLL_BANDWIDTH
#define HYBRID_LOCKED_PLL_BANDWIDTH					0.80E-3
#define HYBRID_INITIAL_PERIOD_LOCKED_PLL_BANDWIDTH	1.00E-3
#define COHERENT_HYBRID_LOCKED_PLL_BANDWIDTH		2.00E-3

#ifdef __cplusplus
}
#endif

#endif

