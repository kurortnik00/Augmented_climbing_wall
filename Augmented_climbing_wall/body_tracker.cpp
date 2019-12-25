#include <iostream>
#include "body_tracker.h"

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
    if (pInterfaceToRelease != NULL)
    {
        pInterfaceToRelease->Release();
        pInterfaceToRelease = NULL;
    }
}

/// <summary>
/// Constructor
/// </summary>
BodyTracker::BodyTracker() :
    m_nPreviousTime(0),
    m_pKinectSensor(NULL),
    m_pCoordinateMapper(NULL),
    m_pBodyFrameReader(NULL),
    m_pBodyIndexFrameReader(NULL)
{
	/*bodyTexturePixels.assign(BodyTracker::cDepthWidth * BodyTracker::cDepthHeight * 4, 0);
	bodyTexturePixels_outline.assign(BodyTracker::cDepthWidth * BodyTracker::cDepthHeight * 4, 0);
    simplifiedBodyMask.assign(BodyTracker::cDepthWidth, std::vector<int>(BodyTracker::cDepthHeight));*/
}


/// <summary>
/// Destructor
/// </summary>
BodyTracker::~BodyTracker()
{
    // done with body index frame reader
    SafeRelease(m_pBodyIndexFrameReader);

    // done with body frame reader
    SafeRelease(m_pBodyFrameReader);

    // done with coordinate mapper
    SafeRelease(m_pCoordinateMapper);

    // close the Kinect Sensor
    if (m_pKinectSensor)
    {
        m_pKinectSensor->Close();
    }

    SafeRelease(m_pKinectSensor);
}

void BodyTracker::Run()
{
    InitializeDefaultSensor();
}


void BodyTracker::Update(bool getMask)
{
    if ((!m_pBodyFrameReader) || (!m_pBodyIndexFrameReader))
    {
        return;
    }
    IBodyFrame* pBodyFrame = NULL;
    IBodyIndexFrame* pBodyIndexFrame = NULL;

    HRESULT hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

    if (SUCCEEDED(hr))
    {
        INT64 nTime = 0;

        hr = pBodyFrame->get_RelativeTime(&nTime);

        IBody* ppBodies[BODY_COUNT] = { 0 };

        if (SUCCEEDED(hr))
        {
            hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
        }

        if (SUCCEEDED(hr))
        {
            ProcessBody(nTime, BODY_COUNT, ppBodies);
        }

        for (int i = 0; i < _countof(ppBodies); ++i)
        {
            SafeRelease(ppBodies[i]);
        }
    }

	if (getMask)
	{
		HRESULT hr = m_pBodyIndexFrameReader->AcquireLatestFrame(&pBodyIndexFrame);

		if (SUCCEEDED(hr))
		{
			bool logDescription = false;
			if (logDescription)
			{
                logBodyIndexFrameDescription(pBodyIndexFrame);

				logDescription = false;
			}

			//byte* buffer;
			//unsigned capacity;
			//pBodyIndexFrame->AccessUnderlyingBuffer(&capacity, &buffer);

			//const byte* bodyMask = const_cast<const byte*>(buffer);
			//outlinePixelVector.erase(outlinePixelVector.begin(), outlinePixelVector.end());
			//for (int i = 0; i < BodyTracker::cDepthWidth; i++)
			//{
			//	for (int j = 1; j < BodyTracker::cDepthHeight - 1; j++)
			//	{
			//		int idx = i * BodyTracker::cDepthHeight + j;
   //                 simplifiedBodyMask[i][j] = bodyMask[idx];
			//		if (bodyMask[idx] != 255)
			//		{
			//			if ((bodyMask[idx - 1] != 255) && (bodyMask[idx + 1] != 255))
			//			{
			//				/*if (foundBody)
			//				{
			//					LOG(INFO) « "FOUND BODY";
			//					foundBody = false;
			//				}*/
			//				bodyTexturePixels[idx * 4] = 0;
			//				bodyTexturePixels[idx * 4 + 1] = 0;
			//				bodyTexturePixels[idx * 4 + 2] = 0;
			//				bodyTexturePixels[idx * 4 + 3] = 255;

			//			}
			//			else
			//			{
			//				sf::Uint8 value = (bodyMask[idx] + 1) * 30;
			//				bodyTexturePixels[idx * 4] = value;
			//				bodyTexturePixels[idx * 4 + 1] = value;
			//				bodyTexturePixels[idx * 4 + 2] = value;
			//				bodyTexturePixels[idx * 4 + 3] = 255;

			//				//TODO 
			//				//not work 
			//				outlinePixelVector.push_back(sf::Vector2f(j, i));  ///shoud make vector with outlinePixels, and use them in itaraction with buttons and game objects 

			//			}
			//		}

			//		else
			//		{
			//			bodyTexturePixels[idx * 4] = 0;
			//			bodyTexturePixels[idx * 4 + 1] = 0;
			//			bodyTexturePixels[idx * 4 + 2] = 0;
			//			bodyTexturePixels[idx * 4 + 3] = 255;
			//		}
			//	}
			//}
		}
	}

    SafeRelease(pBodyFrame);
    SafeRelease(pBodyIndexFrame);
}


HRESULT BodyTracker::InitializeDefaultSensor()
{
    HRESULT hr;

    hr = GetDefaultKinectSensor(&m_pKinectSensor);
    if (FAILED(hr))
    {
        std::cout << "No ready Kinect found!";
        return E_FAIL;
    }

    if (m_pKinectSensor)
    {
        // Initialize the Kinect and get coordinate mapper and the body reader
        IBodyFrameSource* pBodyFrameSource = NULL;
        IBodyIndexFrameSource* pBodyIndexFrameSource = NULL;

        hr = m_pKinectSensor->Open();

        if (SUCCEEDED(hr))
        {
            hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
        }

        if (SUCCEEDED(hr))
        {
            hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
        }

        if (SUCCEEDED(hr))
        {
            hr = m_pKinectSensor->get_BodyIndexFrameSource(&pBodyIndexFrameSource);
        }

        if (SUCCEEDED(hr))
        {
            hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
        }

        if (SUCCEEDED(hr))
        {
            hr = pBodyIndexFrameSource->OpenReader(&m_pBodyIndexFrameReader);
        }

        SafeRelease(pBodyFrameSource);
        SafeRelease(pBodyIndexFrameSource);
    }

    return hr;
}

void BodyTracker::ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies)
{
    HRESULT hr;

    if (m_pCoordinateMapper)
    {
        int width = 640;
        int height = 280;
        int nTrackedBodies = 0;

        // Calculate time delta from previous frame
        delta = static_cast<float>(nTime - m_nPreviousTime) / timeStampScale;
        m_nPreviousTime = nTime;

        left_idx = -1;
        right_idx = -1;
        for (int i = 0; i < nBodyCount; ++i)
        {
            IBody* pBody = ppBodies[i];
            massCenter[i] = sf::Vector2f(0.f, 0.f);
            if (pBody)
            {
                BOOLEAN bTracked = false;
                hr = pBody->get_IsTracked(&bTracked);

                isTracked[i] = bTracked;
                if (bTracked)
                {
                    nTrackedBodies++;

                    Joint joints[JointType_Count];

                    hr = pBody->GetJoints(_countof(joints), joints);

                    if (SUCCEEDED(hr))
                    {
                        for (int j = 0; j < _countof(joints); ++j)
                        {
                            trackPointsXY[i][j] = GetProjection(BodyToScreen(joints[j].Position, width, height));
                            trackDepthPoint[i][j] = joints[j].Position.Z;

                            massCenter[i] = massCenter[i] + trackPointsXY[i][j];
                        }
                        massCenter[i] = massCenter[i] / static_cast<float>(_countof(joints));
                        calcAllJoints_timeAveraged_PointsXY(i);
                        calcAllJoints_timeAveraged_DepthPoints(i);

                        for (int j = 0; j < static_cast<int>(Limbs::Type::Count); ++j)
                        {
                            sf::Vector2f newPointXY = LimbPointsXY(i, static_cast<Limbs::Type>(j));
                            limbVelocitiesXY[i][j] = (limbPointsXY[i][j] - newPointXY) / delta;
                            limbPointsXY[i][j] = newPointXY;
                            limbDepthPoint[i][j] = LimbDepthPoint(i, static_cast<Limbs::Type>(j));
                        }
                        calc_arms_legs_timeAveraged_PointsXY(i);
                        calc_arms_legs_timeAveraged_DepthPoints(i);
                    }

                    if ((left_idx == -1) || (massCenter[i].x < massCenter[left_idx].x))
                    {
                        left_idx = i;
                    }
                    if ((right_idx == -1) || (massCenter[i].x > massCenter[right_idx].x))
                    {
                        right_idx = i;
                    }
                }
            }
        }

        if (left_idx == right_idx)
        {
            right_idx = -1;
        }
    }
}


sf::Vector2f BodyTracker::BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height)
{
    // Calculate the body's position on the screen
    DepthSpacePoint depthPoint = { 0 };
    m_pCoordinateMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);

    float screenPointX = static_cast<float>(depthPoint.X * width) / cDepthWidth;
    float screenPointY = static_cast<float>(depthPoint.Y * height) / cDepthHeight;

    return sf::Vector2f(screenPointX, screenPointY);
}

int BodyTracker::getSingleBodyId()
{
    return left_idx;
}

int BodyTracker::getBodyId(bool left)
{
    return (left) ? left_idx : right_idx;
}

bool BodyTracker::isBodyTracked(int i)
{
    if ((i < 0) || (i >= BODY_COUNT))
    {
        return false;
    }
    return isTracked[i];
}

sf::Vector2f BodyTracker::LimbPointsXY(int i, Limbs::Type limb)
{
    sf::Vector2f point(0.f, 0.f);
    if (i < 0)
    {
        return point;
    }

    auto joints = limbJoints[limb];
    for (int j = 0; j < joints.size(); j++)
    {
        point += trackPointsXY[i][static_cast<int>(joints[j])];
    }
    point /= static_cast<float>(joints.size());
    return point;
}

float BodyTracker::LimbDepthPoint(int i, Limbs::Type limb)
{
    float point = 0.f;

    if (i < 0)
    {
        return point;
    }

    auto joints = limbJoints[limb];
    for (int j = 0; j < joints.size(); j++)
    {
        point += trackDepthPoint[i][static_cast<int>(joints[j])];
    }
    point /= static_cast<float>(joints.size());

    return point;
}

void BodyTracker::calcAllJoints_timeAveraged_PointsXY(int body_id)
{
	JointPoints_buffer jointPoints;

	for (int i = 0; i < JointType_Count; i++)
	{
		jointPoints.joints[i] = trackPointsXY[body_id][i];
	}

	buffer.push_back(jointPoints);
	if (buffer.size() > 500) buffer.erase(buffer.begin());
	int flag = 0;
	for (auto& i : buffer)
	{
		for (int j = 0; j < JointType_Count; j++)
		{
			if (flag == 0)
			{
				trackPointsXY_timeAveraged[body_id][j] = i.joints[j];
			}
			else
			{
                trackPointsXY_timeAveraged[body_id][j] += i.joints[j];
			}
		}
		flag = 1;
	}
	for (int j = 0; j < JointType_Count; j++)
	{
        trackPointsXY_timeAveraged[body_id][j] /= static_cast<float>(buffer.size());
	}
}


void BodyTracker::calcAllJoints_timeAveraged_DepthPoints(int body_id)
{
	JointPoints_Depthbuffer jointDepthPoints;
	for (int i = 0; i < JointType_Count; i++)
	{
		jointDepthPoints.jointsDepth[i] = trackDepthPoint[body_id][i];
	}
	depthBuffer.push_back(jointDepthPoints);
	if (depthBuffer.size() > 5) depthBuffer.erase(depthBuffer.begin());
	int flag = 0;
	for (auto& i : depthBuffer)
	{
		for (int j = 0; j < JointType_Count; j++)
		{
			if (flag == 0)
			{

				trackDepthPoint_timeAveraged[body_id][j] = i.jointsDepth[j];
			}
			else
			{
				trackDepthPoint_timeAveraged[body_id][j] += i.jointsDepth[j];
			}
		}
		flag = 1;
	}
	for (int j = 0; j < JointType_Count; j++)
	{
		trackDepthPoint_timeAveraged[body_id][j] /= static_cast<float>(depthBuffer.size());
	}
}

void BodyTracker::calc_arms_legs_timeAveraged_PointsXY(int body_id)
{
	sf::Vector2f previous_timeAveraged_Point[static_cast<int>(Limbs::Type::Count)];
    for (int i = 0; i < static_cast<int>(Limbs::Type::Count); i++)
    {
        previous_timeAveraged_Point[i] = limbPointsXY_timeAveraged[body_id][i];
    }

	LimbsPoints_buffer limbPoints;
	for (int i = 0; i < static_cast<int>(Limbs::Type::Count); i++)
	{
		limbPoints.limbs[i] = limbPointsXY[body_id][static_cast<int>(i)];
	}

	limbs_buffer.push_back(limbPoints);
	if (limbs_buffer.size() > 2000) limbs_buffer.erase(limbs_buffer.begin());
	int flag = 0;
	for (auto& i : limbs_buffer)
	{
		for (int j = 0; j < static_cast<int>(Limbs::Type::Count); j++)
		{
			if (flag == 0)
			{
				limbPointsXY_timeAveraged[body_id][j] = i.limbs[j];
			}
			else
			{
                limbPointsXY_timeAveraged[body_id][j] += i.limbs[j];
			}
		}
		flag = 1;
	}
	for (int j = 0; j < static_cast<int>(Limbs::Type::Count); j++)
	{
        limbPointsXY_timeAveraged[body_id][j] /= static_cast<float>(limbs_buffer.size());
        limbVelocitiesXY_timeAveraged[body_id][j] = (limbPointsXY_timeAveraged[body_id][j] - previous_timeAveraged_Point[j]) / delta;
	}
}

void BodyTracker::calc_arms_legs_timeAveraged_DepthPoints(int body_id)
{
	float timeAveraged_DepthPoint[static_cast<int>(Limbs::Type::Count)];

	LimbsPoints_Depthbuffer limbsDepthPoints;
	for (int i = 0; i < static_cast<int>(Limbs::Type::Count); i++)
	{
		limbsDepthPoints.limbsDepth[i] = limbDepthPoint[body_id][static_cast<int>(i)];
	}
	limbs_depthBuffer.push_back(limbsDepthPoints);
	if (limbs_depthBuffer.size() > 2000) limbs_depthBuffer.erase(limbs_depthBuffer.begin());
	int flag = 0;
	for (auto& i : limbs_depthBuffer)
	{
		for (int j = 0; j < static_cast<int>(Limbs::Type::Count); j++)
		{
			if (flag == 0)
			{
				limbDepthPoint_timeAveraged[body_id][j] = i.limbsDepth[j];
			}
			else
			{
                limbDepthPoint_timeAveraged[body_id][j] += i.limbsDepth[j];
			}
		}
		flag = 1;
	}
	for (int j = 0; j < static_cast<int>(Limbs::Type::Count); j++)
	{
        limbDepthPoint_timeAveraged[body_id][j] /= static_cast<float>(limbs_depthBuffer.size());
	}
}

sf::Vector2f BodyTracker::GetProjection (const sf::Vector2f point)
{
    sf::Vector2f projection;

    projection.x = 1920 * (1 - point.x / 640);
    projection.y = point.y * 1200 / 280;

    return projection;
}

sf::Uint8* BodyTracker::getBodyMask()
{
	return &bodyTexturePixels[0];
}

std::vector<std::vector<int>>& BodyTracker::getSimplifiedBodyMask()
{
    return simplifiedBodyMask;
}

sf::Uint8* BodyTracker::get_outline_BodyMask()
{
	return &bodyTexturePixels_outline[0];
}

std::vector<sf::Vector2f>* BodyTracker::getOutlinePixelVector()
{
	return &outlinePixelVector;
}

sf::Vector2f BodyTracker::getOutlinePixel(int i)
{
	return outlinePixelVector[i];
}

sf::Vector2f BodyTracker::getJointPointsXY(Joints::Type joint, int body_id)
{
    if (body_id < 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }
    return trackPointsXY[body_id][static_cast<int>(joint)];
}

float BodyTracker::getJointDepthPoint(Joints::Type joint, int body_id)
{
    if (body_id < 0)
    {
        return 0.f;
    }
    return trackDepthPoint[body_id][static_cast<int>(joint)];
}

sf::Vector2f BodyTracker::getLimbPointsXY(Limbs::Type limb, int body_id)
{
    if (body_id < 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }
    return limbPointsXY[body_id][static_cast<int>(limb)];
}

float BodyTracker::getLimbDepthPoints(Limbs::Type limb, int body_id)
{
    if (body_id < 0)
    {
        return 0.f;
    }
    return limbDepthPoint[body_id][static_cast<int>(limb)];
}

sf::Vector2f BodyTracker::getLimbVelocitiesXY(Limbs::Type limb, int body_id)
{
    if (body_id < 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }
    return limbVelocitiesXY[body_id][static_cast<int>(limb)];
}

sf::Vector2f BodyTracker::getAllJoints_timeAveraged_PointsXY(int joint, int body_id)
{
    if (body_id < 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }
    return trackPointsXY_timeAveraged[body_id][joint];
}

float BodyTracker::getAllJoints_timeAveraged_DepthPoints(int joint, int body_id)
{
    if (body_id < 0)
    {
        return 0.f;
    }
    return trackDepthPoint_timeAveraged[body_id][joint];
}

sf::Vector2f BodyTracker::get_arms_legs_timeAveraged_PointsXY(int limb, int body_id)
{
    if (body_id < 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }
    return limbPointsXY_timeAveraged[body_id][limb];
}

float BodyTracker::get_arms_legs_timeAveraged_DepthPoints(int limb, int body_id)
{
    if (body_id < 0)
    {
        return 0.f;
    }
    return limbDepthPoint_timeAveraged[body_id][limb];
}

sf::Vector2f BodyTracker::get_arms_legs_timeAveraged_VelocitiesXY(Limbs::Type limb, int body_id)
{
    if (body_id < 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }
    return limbVelocitiesXY_timeAveraged[body_id][static_cast<int>(limb)];
}

void BodyTracker::SimplifyBodyMask()
{
    /*for (int i = 0; i < BodyTracker::cDepthWidth; i++)
    {
        for (int j = 0; j < BodyTracker::cDepthHeight; j++)
        {
            if (simplifiedBodyMask[i][j] == left_idx)
            {
                simplifiedBodyMask[i][j] = 1;
            }
            else if (simplifiedBodyMask[i][j] == right_idx)
            {
                simplifiedBodyMask[i][j] = 2;
            }
            else
            {
                simplifiedBodyMask[i][j] = 0;
            }
        }
    }*/
}

void BodyTracker::logBodyIndexFrameDescription(IBodyIndexFrame * pBodyIndexFrame)
{
    IFrameDescription* pBodyIndexFrameDescription = NULL;

    int width, height;
    unsigned bytesPerPixel, lengthInPixels;
    float diagonalFieldOfView, horizontalFieldOfView, verticalFieldOfView;

    pBodyIndexFrame->get_FrameDescription(&pBodyIndexFrameDescription);
    pBodyIndexFrameDescription->get_BytesPerPixel(&bytesPerPixel);
    pBodyIndexFrameDescription->get_DiagonalFieldOfView(&diagonalFieldOfView);
    pBodyIndexFrameDescription->get_HorizontalFieldOfView(&horizontalFieldOfView);
    pBodyIndexFrameDescription->get_VerticalFieldOfView(&verticalFieldOfView);
    pBodyIndexFrameDescription->get_Width(&width);
    pBodyIndexFrameDescription->get_Height(&height);
    pBodyIndexFrameDescription->get_LengthInPixels(&lengthInPixels);

    /*LOG(INFO) << "------ BODY INDEX FRAME DESCRIPTION -----";
    LOG(INFO) << "Frame size: " << width << " x " << height;
    LOG(INFO) << "Field of view (degrees): horizontal - " << horizontalFieldOfView

    LOG(INFO) << "------ END BODY INDEX FRAME DESCRIPTION -----";*/
}