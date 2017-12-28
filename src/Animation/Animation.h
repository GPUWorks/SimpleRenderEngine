#pragma once

#include "AnimationTrack.h"
#include <map>
namespace SRE {

	class Animation {

	public:

		typedef std::map<unsigned short, ObjectAnimationTrack::ptr> ObjectTrackMap;
		//��������켣��ʱ��Ӧ��collect��һ��keyframe���У�����ʱ��
		

	protected:
		void collectTrackToKeyFrames(std::vector<float>& keyFrameTimes);

		typedef std::vector<float> KeyFrameTimeList;
		mutable KeyFrameTimeList mKeyFrameTimes;

		ObjectTrackMap _objectAnimationTracks;
	};

	
}