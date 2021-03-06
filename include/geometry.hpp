
#pragma once

#include <iostream>
#include <Eigen/Core>


using Eigen::Vector3d;
using std::pair;


/******************************************************************
* > class Plane                                                   *
* The representation of a plane in 3D space.                      *
* The four parameters are scaled so that a,b,c is an unit vector. *
* See the comments in .cpp file.                                  *
******************************************************************/
class Plane {
	
	protected:

		// plane coefficients
		Vector3d abc;
		double d;

	protected:

		// methods
		Vector3d randomNormal(void) const;

	public:

		// construct
		Plane(double a, double b, double c, double d);
		Plane(void): Plane(1,0,0,0) {}
		Plane(const Vector3d abc, double d);

		// const methods
		pair<Vector3d, double> getParams(void) const { return {abc, d}; }
		double distanceOfPoint(const Vector3d& point) const;
		pair<Vector3d, Vector3d> toPointAndNorm(void) const;

		// other methods
		virtual Plane& setPlane(const Vector3d& abc, double d);
		virtual Plane& setRandomPlane(double d1, double d2);
		virtual Plane& fromPointAndNorm(const Vector3d& point,
				const Vector3d& norm);

		// operator
		bool operator==(const Plane& other) const;
		friend std::ostream& operator<<(std::ostream& out, const Plane& p);

};


/*************************************************************************
* > class PlaneFunction                                                  *
* Linear function R^2 -> R. The Plane is used as representation of       *
* the linear function. x and y are the parameters, z is taken as result. *
* NOTE: parameter c can't be 0..                                         *
* See the comments in .cpp file.                                         *
*************************************************************************/
class PlaneFunction: public Plane {

	private:

		Vector3d fAbc;    // Function params. Added for to speed up operator()
	
	private:

		// private method
		void updateFunParams(void);

	public:

		static const double Z_EPS;

		// construct
		PlaneFunction(void): Plane(0,0,1,0) {}
		PlaneFunction(double a, double b, double c);

		// const methods
		const Vector3d& getFunParams(void) const;
		PlaneFunction getNeighbourFunction(double x, double y,
				double deltaZ, double deltaAng) const;
		PlaneFunction getNeighbourFunction(double x, double y,
				double minZ, double maxZ, double deltaAng) const;

		// other methods
		PlaneFunction& setPlane(const Vector3d& abc, double d) override;
		PlaneFunction& setRandomPlane(double d1, double d2) override;
		PlaneFunction& setRandomFunction(double x, double y,
				double min, double max, double minAngle, double maxAngle);
		PlaneFunction& fromPointAndNorm(const Vector3d& point,
				const Vector3d& norm) override;
		
		// operator
		double operator()(double x, double y) const;
		friend std::ostream& operator<<(std::ostream& out, const PlaneFunction& p);

		// static
		inline bool areFunctionParams(Vector3d p) const;

};
