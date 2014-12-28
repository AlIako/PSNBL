

#ifndef __DR_CORE2_DUMPING_SPRING__
#define __DR_CORE2_DUMPING_SPRING__

/*! \brief class for a dumping spring system
 *
 *  Ursprungsidee kommt aus dem Buch Gems4.
 *  Eine Variable läuft auf ihren Ziel Wert zu,
 *  durch eine Feder geführt
 *
 *  @author Dario Rekowski
 *  @date 22.11.10
 */

class DRDampingSpring
{
public:
        //! \brief constructor with parameters
        //! \param damping damping constant
        //!        for short moving time: damping = 2*WURZEL(spring)
        //! \param spring spring constant
        //!		    for short moving time: spring = (dumping/2)²
        DRDampingSpring(double damping, double spring);

        //! constructor without parameters (both set to 1)
        DRDampingSpring();

        //! \brief to set both constants
        //! \param damping damping constant
        //!        for short moving time: damping = 2*WURZEL(spring)
        //! \param spring spring constant
        //!		    for short moving time: spring = (dumping/2)²
        void setParameter(double damping, double spring);

        //! \brief to set manually the current value
        inline void setCurrent(double current) {mCurrent = current; mVelocity = 0.0f;}

        //! \brief update the current value (returned by operator DRReal())
        //! \param timeSinceLastFrame times in second, since last frame
        void update(double timeSinceLastFrame);

        //! \brief operator DRReal()
        //! \return current value
        inline operator double() const	{return mCurrent;}
		//inline operator int32() const {return (int32)mCurrent;}

        //! \brief assign operator
        //! \param target intern mTarget will be set to target
        inline void operator = (double target) {mTarget = target;}

        inline void operator += (double additional) {mCurrent += additional;}

        //! \return intern mTarget
        inline const double& getTarget() const {return mTarget;}

        inline const double& getVelocity() const {return mVelocity;}

private:
        // damping constant
        double  mDamping;
        // spring constant
        double  mSpring;
        // target value (to reach)
        double			mTarget;
        // from struct use to calculate
        double			mVelocity;
        // current value (return for operator DRReal())
        double			mCurrent;

};

/*   -- S A M P L E --  *\

  DampingSpring value(damping, spring);
  or
  DampingSpring value;
  value.setParameter(damping, spring)

  value = target;
  value.update(timeSinceLastFrame)
  DRReal current = value;
  */

/*
class CORE_API DRSpring
{
public:
	DRSpring();

	void setVar(DRReal value, DRReal time);
	void update(DRReal deltaTime);

	operator DRReal() const {return mVar;}
	DRReal operator = (DRReal value);

	bool hasReachedTarget() const;
private:
	DRReal mVar;		// current value
	DRReal mTarget;		// target value
	DRReal mDelta;		// difference between begin and end value
	DRReal mTime;		// current Time
	DRReal mTimeTarget;	// target time
};
//*/

#endif //__DR_CORE2_DUMPING_SPRING__
