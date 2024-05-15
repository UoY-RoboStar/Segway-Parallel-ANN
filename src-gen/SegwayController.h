#ifndef ROBOCALC_CONTROLLERS_SEGWAYCONTROLLER_H_
#define ROBOCALC_CONTROLLERS_SEGWAYCONTROLLER_H_

#include "SegwayRP.h"
#include "RoboCalcAPI/Controller.h"
#include "DataTypes.h"

#include "BalanceSTM.h"
#include "AnglePID.h"
#include "SpeedPID.h"
#include "RotationPID.h"

class SegwayController: public robocalc::Controller 
{
public:
	SegwayController(SegwayRP& _platform) : platform(&_platform){};
	SegwayController() : platform(nullptr){};
	
	~SegwayController() = default;
	
	void Execute()
	{
		balanceSTM.execute();
		anglePID.execute();
		speedPID.execute();
		rotationPID.execute();
	}
	
	struct Channels
	{
		SegwayController& instance;
		Channels(SegwayController& _instance) : instance(_instance) {}
		
		EventBuffer* tryEmitLeftMotorVelocity(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveLeftMotorVelocity(args))
				instance.balanceSTM.leftMotorVelocity_in.trigger(sender, args);
				
			return &instance.balanceSTM.leftMotorVelocity_in;
		}
		
		EventBuffer* tryEmitRightMotorVelocity(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveRightMotorVelocity(args))
				instance.balanceSTM.rightMotorVelocity_in.trigger(sender, args);
				
			return &instance.balanceSTM.rightMotorVelocity_in;
		}
		
		EventBuffer* tryEmitAngle(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveAngle(args))
				instance.balanceSTM.angle_in.trigger(sender, args);
				
			return &instance.balanceSTM.angle_in;
		}
		
		EventBuffer* tryEmitGyroX(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveGyroX(args))
				instance.balanceSTM.gyroX_in.trigger(sender, args);
				
			return &instance.balanceSTM.gyroX_in;
		}
		
		EventBuffer* tryEmitGyroY(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveGyroY(args))
				instance.balanceSTM.gyroY_in.trigger(sender, args);
				
			return &instance.balanceSTM.gyroY_in;
		}
		
		EventBuffer* tryEmitGyroZ(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveGyroZ(args))
				instance.balanceSTM.gyroZ_in.trigger(sender, args);
				
			return &instance.balanceSTM.gyroZ_in;
		}
		
		EventBuffer* tryEmitAngleOutputE(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveAngleOutputE(args))
				instance.balanceSTM.angleOutputE_in.trigger(sender, args);
				
			return &instance.balanceSTM.angleOutputE_in;
		}
		
		EventBuffer* tryEmitAnewError(void* sender, std::tuple<double> args)
		{
			if(instance.anglePID.canReceiveAnewError(args))
				instance.anglePID.anewError_in.trigger(sender, args);
				
			return &instance.anglePID.anewError_in;
		}
		
		EventBuffer* tryEmitAdiff(void* sender, std::tuple<double> args)
		{
			if(instance.anglePID.canReceiveAdiff(args))
				instance.anglePID.adiff_in.trigger(sender, args);
				
			return &instance.anglePID.adiff_in;
		}
		
		EventBuffer* tryEmitSpeedOutputE(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveSpeedOutputE(args))
				instance.balanceSTM.speedOutputE_in.trigger(sender, args);
				
			return &instance.balanceSTM.speedOutputE_in;
		}
		
		EventBuffer* tryEmitSnewError(void* sender, std::tuple<double> args)
		{
			if(instance.speedPID.canReceiveSnewError(args))
				instance.speedPID.snewError_in.trigger(sender, args);
				
			return &instance.speedPID.snewError_in;
		}
		
		EventBuffer* tryEmitRotationOutputE(void* sender, std::tuple<double> args)
		{
			if(instance.balanceSTM.canReceiveRotationOutputE(args))
				instance.balanceSTM.rotationOutputE_in.trigger(sender, args);
				
			return &instance.balanceSTM.rotationOutputE_in;
		}
		
		EventBuffer* tryEmitRdiff(void* sender, std::tuple<double> args)
		{
			if(instance.rotationPID.canReceiveRdiff(args))
				instance.rotationPID.rdiff_in.trigger(sender, args);
				
			return &instance.rotationPID.rdiff_in;
		}
		
	};
	
	Channels channels{*this};
	
	SegwayRP* platform;
	BalanceSTM_StateMachine<SegwayController> balanceSTM{*platform, *this, &balanceSTM};
	AnglePID_StateMachine<SegwayController> anglePID{*platform, *this, &anglePID};
	SpeedPID_StateMachine<SegwayController> speedPID{*platform, *this, &speedPID};
	RotationPID_StateMachine<SegwayController> rotationPID{*platform, *this, &rotationPID};
};

#endif
