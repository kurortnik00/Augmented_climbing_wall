#pragma once

#include <SFML/System.hpp>
#include <vector>
#include <unordered_map>
#include "stdafx.h"

namespace Joints
{
    enum class Type
    {
        SPINEBASE,
        SPINEMID,
        NECK,
        HEAD,
        SHOULDERLEFT,
        ELBOWLEFT,
        WRISTLEFT,
        HANDLEFT,
        SHOULDERRIGHT,
        ELBOWRIGHT,
        WRISTRIGHT,
        HANDRIGHT,
        HIPLEFT,
        KNEELEFT,
        ANKLELEFT,
        FOOTLEFT,
        HIPRIGHT,
        KNEERIGHT,
        ANKLERIGHT,
        FOOTRIGHT,
        SPINESHOULDER,
        HANDTIPLEFT,
        THUMBLEFT,
        HANDTIPRIGHT,
        THUMBRIGHT,
    };
};

namespace Limbs
{
    enum class Type
    {
        LEFT_HAND  = 0,
        RIGHT_HAND = 1,
        LEFT_FOOT  = 2,
        RIGHT_FOOT = 3,
        Count = (RIGHT_FOOT + 1)
    };
};

class BodyTracker
{
    static const int cDepthWidth = 512;
    static const int cDepthHeight = 424;

    // Timestamp is measured in 100-nanosecond units
    static const int timeStampScale = 10000000; 

public:
    /// <summary>
    /// Constructor
    /// </summary>
    BodyTracker();

    /// <summary>
    /// Destructor
    /// </summary>
    ~BodyTracker();

    /// <summary>
    /// Creates the main window and begins processing
    /// </summary>
    void                    Run();

    /// <summary>
    /// Main processing function
    /// </summary>
    void                    Update(bool getMask);
    void                    SimplifyBodyMask();

    /// <summary>
    /// Get body ID for left and right players in single-player mode
    /// <summary>
    int                     getSingleBodyId();

    /// <summary>
    /// Get body ID for left and right players in two-player mode
    /// <summary>
    int                     getBodyId(bool left);

    byte *					getBodyMask();
    std::vector<std::vector<int>>& getSimplifiedBodyMask();
	sf::Uint8*				get_outline_BodyMask();
	std::vector<sf::Vector2f>* getOutlinePixelVector();
	sf::Vector2f			getOutlinePixel(int i);
    sf::Vector2f            GetProjection(const sf::Vector2f point);
    sf::Vector2f            getJointPointsXY(Joints::Type joint, int body_id);
    float                   getJointDepthPoint(Joints::Type i, int body_id);
    sf::Vector2f            getLimbPointsXY(Limbs::Type limb, int body_id);
    float                   getLimbDepthPoints(Limbs::Type limb, int body_id);
    sf::Vector2f			getLimbVelocitiesXY(Limbs::Type limb, int body_id);
    sf::Vector2f            getAllJoints_timeAveraged_PointsXY(int limb, int body_id);
    float                   getAllJoints_timeAveraged_DepthPoints(int limb, int body_id);
    sf::Vector2f            get_arms_legs_timeAveraged_PointsXY(int limb, int body_id);
    float                   get_arms_legs_timeAveraged_DepthPoints(int limb, int body_id);
    sf::Vector2f            get_arms_legs_timeAveraged_VelocitiesXY(Limbs::Type limb, int body_id);

private:
    // Timestamp of previous frame
    INT64                   m_nPreviousTime;

    // Current Kinect
    IKinectSensor*          m_pKinectSensor;
    ICoordinateMapper*      m_pCoordinateMapper;

    // Body reader
    IBodyFrameReader*       m_pBodyFrameReader;

    // Body index reader
    IBodyIndexFrameReader* m_pBodyIndexFrameReader;

    // Joint positions for all bodies
    Joint trackPoints[BODY_COUNT][JointType_Count];
    sf::Vector2f trackPointsXY[BODY_COUNT][JointType_Count];
    float trackDepthPoint[BODY_COUNT][JointType_Count];

    // Limb positions and velocities for all bodies
    sf::Vector2f limbPointsXY[BODY_COUNT][static_cast<int>(Limbs::Type::Count)];
    float limbDepthPoint[BODY_COUNT][static_cast<int>(Limbs::Type::Count)];
    sf::Vector2f limbVelocitiesXY[BODY_COUNT][static_cast<int>(Limbs::Type::Count)];

    // Time averaged joint positions for all bodies
    sf::Vector2f trackPointsXY_timeAveraged[BODY_COUNT][JointType_Count];
    float trackDepthPoint_timeAveraged[BODY_COUNT][JointType_Count];

    // Time averaged limb positions and velocities for all bodies
    sf::Vector2f limbPointsXY_timeAveraged[BODY_COUNT][static_cast<int>(Limbs::Type::Count)];
    float limbDepthPoint_timeAveraged[BODY_COUNT][static_cast<int>(Limbs::Type::Count)];
    sf::Vector2f limbVelocitiesXY_timeAveraged[BODY_COUNT][static_cast<int>(Limbs::Type::Count)];

    // Mass center of all bodies in XY plane
    sf::Vector2f massCenter[BODY_COUNT];

    // Body indices for left and right player
    int left_idx, right_idx;

    // Body status
    bool isTracked[BODY_COUNT];

    // Time delta in seconds between current and previous frames
    float delta;

    // Body mask
	std::vector<sf::Uint8> bodyTexturePixels;
    std::vector<std::vector<int>> simplifiedBodyMask;

	std::vector<sf::Uint8> bodyTexturePixels_outline;

	std::vector<sf::Vector2f> outlinePixelVector;

    /// <summary>
    /// Initializes the default Kinect sensor
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                 InitializeDefaultSensor();

    /// <summary>
    /// Handle new body data
    /// <param name="nTime">timestamp of frame</param>
    /// <param name="nBodyCount">body data count</param>
    /// <param name="ppBodies">body data in frame</param>
    /// </summary>
    void                    ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies);

    /// <summary>
    /// Converts a body point to screen space
    /// </summary>
    /// <param name="bodyPoint">body point to tranform</param>
    /// <param name="width">width (in pixels) of output buffer</param>
    /// <param name="height">height (in pixels) of output buffer</param>
    /// <returns>point in screen-space</returns>
    sf::Vector2f            BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height);

    sf::Vector2f            LimbPointsXY(int i, Limbs::Type limb);
    float                   LimbDepthPoint(int i, Limbs::Type limb);
    void                    calcAllJoints_timeAveraged_PointsXY(int body_id);
    void                    calcAllJoints_timeAveraged_DepthPoints(int body_id);
    void                    calc_arms_legs_timeAveraged_PointsXY(int body_id);
    void                    calc_arms_legs_timeAveraged_DepthPoints(int body_id);
    void                    logBodyIndexFrameDescription(IBodyIndexFrame * pBodyIndexFrame);

	struct JointPoints_buffer
	{
		sf::Vector2f joints[JointType_Count];
	};
	std::vector<JointPoints_buffer> buffer;

	struct LimbsPoints_buffer
	{
		sf::Vector2f limbs[static_cast<int>(Limbs::Type::Count)];
	};
	std::vector<LimbsPoints_buffer> limbs_buffer;

	struct JointPoints_Depthbuffer
	{
		float jointsDepth[JointType_Count];
	};
	std::vector<JointPoints_Depthbuffer> depthBuffer;

	struct LimbsPoints_Depthbuffer
	{
		float limbsDepth[static_cast<int>(Limbs::Type::Count)];
	};
	std::vector<LimbsPoints_Depthbuffer> limbs_depthBuffer;
	
    std::unordered_map<Limbs::Type, std::vector<Joints::Type>> limbJoints = {
        {Limbs::Type::LEFT_HAND, {Joints::Type::HANDLEFT, Joints::Type::WRISTLEFT, 
                                  Joints::Type::HANDTIPLEFT, Joints::Type::THUMBLEFT}},
        {Limbs::Type::RIGHT_HAND, {Joints::Type::HANDRIGHT, Joints::Type::WRISTRIGHT, 
                                   Joints::Type::HANDTIPRIGHT, Joints::Type::THUMBRIGHT}},
        {Limbs::Type::LEFT_FOOT, {Joints::Type::FOOTLEFT, Joints::Type::ANKLELEFT}},
		{Limbs::Type::RIGHT_FOOT, {Joints::Type::FOOTRIGHT, Joints::Type::ANKLERIGHT}},
    };
};
