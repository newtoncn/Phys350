#pragma once

#include <Physics1.h>
#include <Spring.h>

class RopeSimulation : public Simulation                    // An Object To Simulate A Rope Interacting With A Planer Surface And Air
{
public:
	Spring * *  springs;                           // Springs Binding The Masses (There Shall Be [numOfMasses - 1] Of Them)

	Vector3D gravitation;                           // Gravitational Acceleration (Gravity Will Be Applied To All Masses)

	Vector3D ropeConnectionPos;                     // A Point In Space That Is Used To Set The Position Of The
													// First Mass In The System (Mass With Index 0)

	Vector3D ropeConnectionVel;                     // A Variable To Move The ropeConnectionPos (By This, We Ccan Swing The Rope)

	float groundRepulsionConstant;                      // A Constant To Represent How Much The Ground Shall Repel The Masses

	float groundFrictionConstant;                       // A Constant Of Friction Applied To Masses By The Ground
														// (Used For Sliding Of Rope On The Ground)

	float groundAbsorptionConstant;                     // A Constant Of Absorption Friction Applied To Masses By The Ground
														// (Used For Vertical Collisions Of The Rope With The Ground)

	float groundHeight;                         // A Value To Represent The Y Value Of The Ground
												// (The Ground Is A Planer Surface Facing +Y Direction)

	float airFrictionConstant;                      // A Constant Of Air Friction Applied To Masses

	RopeSimulation(                             // A Long Long Constructor With 11 Parameters Starts Here
		int numOfMasses,                        // 1. The Number Of Masses
		float m,                            // 2. Weight Of Each Mass
		float springConstant,                       // 3. How Stiff The Springs Are
		float springLength,                     // 4. The Length That A Spring Does Not Exert Any Force
		float springFrictionConstant,                   // 5. Inner Friction Constant Of Spring
		Vector3D gravitation,                       // 6. Gravitational Acceleration
		float airFrictionConstant,                  // 7. Air Friction Constant
		float groundRepulsionConstant,                  // 8. Ground Repulsion Constant
		float groundFrictionConstant,                   // 9. Ground Friction Constant
		float groundAbsorptionConstant,                 // 10. Ground Absorption Constant
		float groundHeight                      // 11. Height Of The Ground (Y Position)
	) : Simulation(numOfMasses, m)                  // The Super Class Creates Masses With Weights m Of Each
	{
		this->gravitation = gravitation;

		this->airFrictionConstant = airFrictionConstant;

		this->groundFrictionConstant = groundFrictionConstant;
		this->groundRepulsionConstant = groundRepulsionConstant;
		this->groundAbsorptionConstant = groundAbsorptionConstant;
		this->groundHeight = groundHeight;

		for (int a = 0; a < numOfMasses; ++a)                // To Set The Initial Positions Of Masses Loop With For(;;)
		{
			masses[a]->pos.x = a * springLength;         // Set X-Position Of masses[a] With springLength Distance To Its Neighbor
			masses[a]->pos.y = 0;                    // Set Y-Position As 0 So That It Stand Horizontal With Respect To The Ground
			masses[a]->pos.z = 0;                    // Set Z-Position As 0 So That It Looks Simple
		}

		springs = new Spring*[numOfMasses - 1];             // Create [numOfMasses - 1] Pointers For springs
															// ([numOfMasses - 1] Springs Are Necessary For numOfMasses)

		for (a = 0; a < numOfMasses - 1; ++a)                // To Create Everyone Of Each Start A Loop
		{
			// Create The Spring With Index "a" By The Mass With Index "a" And Another Mass With Index "a + 1".
			springs[a] = new Spring(masses[a], masses[a + 1],
				springConstant, springLength, springFrictionConstant);
		}
	}

	void solve()                                // solve() Is Overriden Because We Have Forces To Be Applied
	{
		for (int a = 0; a < numOfMasses - 1; ++a)            // Apply Force Of All Springs
		{
			springs[a]->solve();                 // Spring With Index "a" Should Apply Its Force
		}

		for (int a = 0; a < numOfMasses; ++a)                // Start A Loop To Apply Forces Which Are Common For All Masses
		{
			masses[a]->applyForce(gravitation * masses[a]->m);    // The Gravitational Force
																  // The air friction
			masses[a]->applyForce(-masses[a]->vel * airFrictionConstant);

			if (masses[a]->pos.y < groundHeight)          // Forces From The Ground Are Applied If A Mass Collides With The Ground
			{
				Vector3D v;                 // A Temporary Vector3D

				v = masses[a]->vel;              // Get The Velocity
				v.y = 0;                    // Omit The Velocity Component In Y-Direction

											// The Velocity In Y-Direction Is Omited Because We Will Apply A Friction Force To Create
											// A Sliding Effect. Sliding Is Parallel To The Ground. Velocity In Y-Direction Will Be Used
											// In The Absorption Effect.

											// Ground Friction Force Is Applied            
				masses[a]->applyForce(-v * groundFrictionConstant);

				v = masses[a]->vel;              // Get The Velocity
				v.x = 0;                    // Omit The x And z Components Of The Velocity
				v.z = 0;                    // We Will Use v In The Absorption Effect

											// Above, We Obtained A Velocity Which Is Vertical To The Ground And It Will Be Used In
											// The Absorption Force

				if (v.y < 0)                 // Let's Absorb Energy Only When A Mass Collides Towards The Ground

											 // The Absorption Force Is Applied             
					masses[a]->applyForce(-v * groundAbsorptionConstant);

				// The Ground Shall Repel A Mass Like A Spring.
				// By "Vector3D(0, groundRepulsionConstant, 0)" We Create A Vector In The Plane Normal Direction
				// With A Magnitude Of groundRepulsionConstant.
				// By (groundHeight - masses[a]->pos.y) We Repel A Mass As Much As It Crashes Into The Ground.
				Vector3D force = Vector3D(0, groundRepulsionConstant, 0) *
					(groundHeight - masses[a]->pos.y);

				masses[a]->applyForce(force);            // The Ground Repulsion Force Is Applied
			}
		}
	}

	void simulate(float dt)                         // simulate(float dt) Is Overriden Because We Want To Simulate
													// The Motion Of The ropeConnectionPos
	{
		Simulation::simulate(dt);                   // The Super Class Shall Simulate The Masses

		ropeConnectionPos += ropeConnectionVel * dt;            // Iterate The Positon Of ropeConnectionPos

		if (ropeConnectionPos.y < groundHeight)              // ropeConnectionPos Shall Not Go Under The Ground
		{
			ropeConnectionPos.y = groundHeight;
			ropeConnectionVel.y = 0;
		}

		masses[0]->pos = ropeConnectionPos;              // Mass With Index "0" Shall Position At ropeConnectionPos
		masses[0]->vel = ropeConnectionVel;              // The Mass's Velocity Is Set To Be Equal To ropeConnectionVel
	}

	void setRopeConnectionVel(Vector3D ropeConnectionVel)           // The Method To Set ropeConnectionVel
	{
		this->ropeConnectionVel = ropeConnectionVel;
	}

};