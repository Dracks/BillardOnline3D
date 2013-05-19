//
//  AbstractGameObserver.h
//  BillardOnline3D
//
//  Created by Dracks on 5/19/13.
//
//

#ifndef __BillardOnline3D__AbstractGameObserver__
#define __BillardOnline3D__AbstractGameObserver__

namespace Game{
	class BallInfo;
	class ActionInfo;
	class AbstractGameObserver;
}

#include <iostream>
#include "gameplay.h"
namespace Game{
	enum BallStatus {
		BS_Normal, BS_Out, BS_Inside
	};

	enum ActionType{
		AT_Shoot,
		AT_Place,
	};

	class BallInfo{
	public:
		BallInfo(int keyBall, const BallStatus status,const gameplay::Vector3 position);
		~BallInfo(){}
		int getKey();
		BallStatus getStatus();
		gameplay::Vector3 getPosition();
	private:
		int _keyBall;
		BallStatus _status;
		gameplay::Vector3 _position;
	};

	class ActionInfo{
	public:
		ActionInfo(int keyBall, gameplay::Vector3 position);
		ActionInfo(const gameplay::Vector3 position,const gameplay::Vector3 vectorShot);
		~ActionInfo(){};
		ActionType getAction();
		int getKey();
		gameplay::Vector3 getPosition();
		gameplay::Vector3 getVelocityShot();
	private:
		ActionType _action;
		int _keyBall;
		gameplay::Vector3 _position;
		gameplay::Vector3 _velocityShot;
	};


	class AbstractGameObserver {
	public:
		virtual ~AbstractGameObserver();
		virtual void setAction(int numRound, ActionInfo* action)=0;
		virtual void setResult(int numRound, std::vector<BallInfo> listBallInfo)=0;
		virtual void gameEnd(int numRound, int winner)=0;
		virtual bool commit(int numRound)=0;
	};
}

#endif /* defined(__BillardOnline3D__AbstractGameObserver__) */
