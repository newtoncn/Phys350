/**************************************************************************
File: Physics1.h
Prepared by Erkin Tunca for http://nehe.gamedev.net
力, 速度, 加速度, 位移之间的关系公式:
V = V0 + a*t
S = V0 + (a*t*t)/2 = S0 + V * detat
F = m * a
**************************************************************************/

#include <math.h>

// class Vector3D		---> An object to represent a 3D vector or a 3D point in space
class Vector3D
{
public:
	float x;									// the x value of this Vector3D
	float y;									// the y value of this Vector3D
	float z;									// the z value of this Vector3D

	Vector3D()									// Constructor to set x = y = z = 0
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3D(float x, float y, float z)			// Constructor that initializes this Vector3D to the intended values of x, y and z
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3D& operator= (Vector3D v)			// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector3D operator+ (Vector3D v)				// operator+ is used to add two Vector3D's. operator+ returns a new Vector3D
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator- (Vector3D v)				// operator- is used to take difference of two Vector3D's. operator- returns a new Vector3D
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	Vector3D operator* (float value)			// operator* is used to scale a Vector3D by a value. This value multiplies the Vector3D's x, y and z.
	{
		return Vector3D(x * value, y * value, z * value);
	}

	Vector3D operator/ (float value)			// operator/ is used to scale a Vector3D by a value. This value divides the Vector3D's x, y and z.
	{
		return Vector3D(x / value, y / value, z / value);
	}

	Vector3D& operator+= (Vector3D v)			// operator+= is used to add another Vector3D to this Vector3D.
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3D& operator-= (Vector3D v)			// operator-= is used to subtract another Vector3D from this Vector3D.
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3D& operator*= (float value)			// operator*= is used to scale this Vector3D by a value.
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	Vector3D& operator/= (float value)			// operator/= is used to scale this Vector3D by a value.
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}


	Vector3D operator- ()						// operator- is used to set this Vector3D's x, y, and z to the negative of them.
	{
		return Vector3D(-x, -y, -z);
	}

	float length()								// length() returns the length of this Vector3D
	{
		return sqrtf(x*x + y * y + z * z);
	};

	void unitize()								// unitize() normalizes this Vector3D that its direction remains the same but its length is 1.
	{
		float length = this->length();

		if (length == 0)
			return;

		x /= length;
		y /= length;
		z /= length;
	}

	Vector3D unit()								// unit() returns a new Vector3D. The returned value is a unitized version of this Vector3D.
	{
		float length = this->length();

		if (length == 0)
			return *this;

		return Vector3D(x / length, y / length, z / length);
	}

};

// class Mass			---> An object to represent a mass
class Mass
{
public:
	float m;									// The mass value
	Vector3D pos;								// Position in space
	Vector3D vel;								// Velocity
	Vector3D force;								// Force applied on this mass at an instance

	Mass(float m)								// Constructor
	{
		this->m = m;
	}

	/*
	void applyForce(Vector3D force) method is used to add external force to the mass.
	At an instance in time, several sources of force might affect the mass. The vector sum
	of these forces make up the net force applied to the mass at the instance.
	*/
	/*
	* 在某一时刻, 更新物体所受到的力的方向和大小.
	*
	* */
	void applyForce(Vector3D force)
	{
		this->force += force;					// The external force is added to the force of the mass
	}

	/*
	void init() method sets the force values to zero
	*/
	/*
	* 把物体所受到的力的方向和大小重置为零.
	*
	* */
	void init()
	{
		force.x = 0;
		force.y = 0;
		force.z = 0;
	}

	/*
	void simulate(float dt) method calculates the new velocity and new position of
	the mass according to change in time (dt). Here, a simulation method called
	"The Euler Method" is used. The Euler Method is not always accurate, but it is
	simple. It is suitable for most of physical simulations that we know in common
	computer and video games.
	*/
	/*
	* 经过时间片(dt)后, 更新在力的作用下(force)物体的速度(vel)(包括方向和大
	* 小), 和位置(pos).
	*
	* 在没有力的作用下, 若物体的初始状态是运动的, 则物体做永远的匀速直线运动;
	* 若物体的初始状态是静止的, 则物体将永远静止.
	*
	* */
	void simulate(float dt)
	{
		//      V = V0 + a * detat
		//      F = m * a
		//  ==> V = V0 + (F / m) * detat
		vel += (force / m) * dt;				// Change in velocity is added to the velocity.
												// The change is proportinal with the acceleration (force / m) and change in time

												// S = S0 + V * detat
		pos += vel * dt;						// Change in position is added to the position.
												// Change in position is velocity times the change in time
	}

};

// class Simulation		---> A container object for simulating masses
class Simulation
{
public:
	int numOfMasses;								// number of masses in this container
	Mass** masses;									// masses are held by pointer to pointer. (Here Mass** represents a 1 dimensional array)

	Simulation(int numOfMasses, float m)			// Constructor creates some masses with mass values m
	{
		this->numOfMasses = numOfMasses;

		// Mess *A[3]; 指针数组!
		masses = new Mass*[numOfMasses];			// Create an array of pointers

		for (int a = 0; a < numOfMasses; ++a)		// We will step to every pointer in the array
			masses[a] = new Mass(m);				// Create a Mass as a pointer and put it in the array
	}

	~Simulation()
	{
		release();
	}

	virtual void release()							// delete the masses created
	{
		for (int a = 0; a < numOfMasses; ++a)		// we will delete all of them
		{
			delete(masses[a]);
			masses[a] = NULL;
		}

		delete(masses);
		masses = NULL;
	}

	Mass* getMass(int index)
	{
		if (index < 0 || index >= numOfMasses)		// if the index is not in the array
			return NULL;							// then return NULL

		return masses[index];						// get the mass at the index
	}

	virtual void init()								// this method will call the init() method of every mass
	{
		for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
			masses[a]->init();						// call init() method of the mass
	}

	virtual void solve()							// no implementation because no forces are wanted in this basic container
	{
		// in advanced containers, this method will be overrided and some forces will act on masses
	}

	virtual void simulate(float dt)					// Iterate the masses by the change in time
	{
		for (int a = 0; a < numOfMasses; ++a)		// We will iterate every mass
			masses[a]->simulate(dt);				// Iterate the mass and obtain new position and new velocity
	}

	virtual void operate(float dt)					// The complete procedure of simulation
	{
		init();										// Step 1: reset forces to zero
		solve();									// Step 2: apply forces
		simulate(dt);								// Step 3: iterate the masses by the change in time
	}

};

/*
class ConstantVelocity is derived from class Simulation
It creates 1 mass with mass value 1 kg and sets its velocity to (1.0f, 0.0f, 0.0f)
so that the mass moves in the x direction with 1 m/s velocity.
*/
class ConstantVelocity : public Simulation
{
public:
	ConstantVelocity() : Simulation(1, 1.0f)				//Constructor firstly constructs its super class with 1 mass and 1 kg
	{
		masses[0]->pos = Vector3D(0.0f, 8.0f, 0.0f);		//a mass was created and we set its position to the origin
		masses[0]->vel = Vector3D(5.0f, 0.0f, 0.0f);		//we set the mass's velocity to (1.0f, 0.0f, 0.0f)
	}

};

/*
class MotionUnderGravitation is derived from class Simulation
It creates 1 mass with mass value 1 kg and sets its velocity to (10.0f, 15.0f, 0.0f) and its position to
(-10.0f, 0.0f, 0.0f). The purpose of this application is to apply a gravitational force to the mass and
observe the path it follows. The above velocity and position provides a fine projectile path with a
9.81 m/s/s downward gravitational acceleration. 9.81 m/s/s is a very close value to the gravitational
acceleration we experience on the earth.
*/
class MotionUnderGravitation : public Simulation
{
public:
	// 引力加速度的方向和大小
	Vector3D gravitation;													//the gravitational acceleration

	MotionUnderGravitation(Vector3D gravitation) : Simulation(1, 1.0f)		//Constructor firstly constructs its super class with 1 mass and 1 kg
	{																		//Vector3D gravitation, is the gravitational acceleration
		this->gravitation = gravitation;									//set this class's gravitation
		masses[0]->pos = Vector3D(-0.0f, 0.0f, 0.0f);						//set the position of the mass
		masses[0]->vel = Vector3D(10.0f, 15.0f, 0.0f);						//set the velocity of the mass
	}

	virtual void solve()													//gravitational force will be applied therefore we need a "solve" method.
	{
		//
		// 力和加速度的关系:
		//    F = m * a
		//  其中, m为物体的质量(masses[.]->m), a为加速度(gravitation).
		//
		for (int a = 0; a < numOfMasses; ++a)
			masses[a]->applyForce(gravitation * masses[a]->m);
	}

};

/*
class MassConnectedWithSpring is derived from class Simulation
It creates 1 mass with mass value 1 kg and binds the mass to an arbitrary constant point with a spring.
This point is refered as the connectionPos and the spring has a springConstant value to represent its
stiffness.
*/

/*
*      简谐运动(或简谐振动,谐振)既是最基本也是最简单的一种机械振动. 当某物体进行
*  简谐运动时, 物体所受的力跟位移成正比, 并且力总是指向平衡位置.
*
*      如果用F表示物体受到的回复力, 用x表示小球对于平衡位置的位移, 根据胡克定律,
*  F和x成正比, 它们之间的关系可用下式来表示:
*
*      F = − kx
*
*  式中的k是回复力与位移成正比的比例系数, 不能与弹簧的劲度系数混淆; 负号的意
*  思是: 回复力的方向总跟物体位移的方向相反.
*
**/
class MassConnectedWithSpring : public Simulation
{
public:
	// 回复力与位移成正比的比例系数
	float springConstant;													//more the springConstant, stiffer the spring force
																			// 平衡位置
	Vector3D connectionPos;													//the arbitrary constant point that the mass is connected

	MassConnectedWithSpring(float springConstant) : Simulation(1, 1.0f)		//Constructor firstly constructs its super class with 1 mass and 1 kg
	{
		this->springConstant = springConstant;								//set the springConstant

		connectionPos = Vector3D(0.0f, 10.0f, 0.0f);							// modified by laks to make the spring visible

		masses[0]->pos = connectionPos + Vector3D(10.0f, 0.0f, 0.0f);		//set the position of the mass 10 meters to the right side of the connectionPos
		masses[0]->vel = Vector3D(0.0f, 0.0f, 0.0f);						//set the velocity of the mass to zero
	}

	MassConnectedWithSpring(float springConstant, Vector3D connPos,
		Vector3D origPos) : Simulation(1, 1.0f)
	{
		this->springConstant = springConstant;

		connectionPos = connPos;
		masses[0]->pos = origPos;
		masses[0]->vel = Vector3D(0.0f, 0.0f, 0.0f);
	}

	virtual void solve()													//the spring force will be applied
	{
		for (int a = 0; a < numOfMasses; ++a)								//we will apply force to all masses (actually we have 1 mass, but we can extend it in the future)
		{
			// F = -k * x
			Vector3D springVector = masses[a]->pos - connectionPos;			//find a vector from the position of the mass to the connectionPos
			masses[a]->applyForce(-springVector * springConstant);			//apply the force according to the famous spring force formulation
		}
	}

};

class Spring                                    // An Object To Represent A Spring With Inner Friction Binding Two Masses. The Spring
{                                       // Has A Normal Length (The Length That The Spring Does Not Exert Any Force)
public:
	Mass * mass1;                                // The First Mass At One Tip Of The Spring
	Mass* mass2;                                // The Second Mass At The Other Tip Of The Spring

	float springConstant;                           // A Constant To Represent The Stiffness Of The Spring
	float springLength;                         // The Length That The spring Does Not Exert Any Force
	float frictionConstant;                         // A Constant To be Used For The Inner Friction Of The Spring

	Spring(Mass* mass1, Mass* mass2,
		// Constructor
		float springConstant, float springLength, float frictionConstant)
	{
		this->springConstant = springConstant;               // Set The springConstant
		this->springLength = springLength;               // Set The springLength
		this->frictionConstant = frictionConstant;           // Set The frictionConstant

		this->mass1 = mass1;                     // Set mass1
		this->mass2 = mass2;                     // Set mass2
	}

	void solve()                                // solve() Method: The Method Where Forces Can Be Applied
	{
		Vector3D springVector = mass1->pos - mass2->pos;      // Vector Between The Two Masses

		float r = springVector.length();                // Distance Between The Two Masses

		Vector3D force;                         // Force Initially Has A Zero Value

		if (r != 0)                         // To Avoid A Division By Zero... Check If r Is Zero
											// The Spring Force Is Added To The Force      
			force += -(springVector / r) * (r - springLength) * springConstant;

		force += -(mass1->vel - mass2->vel) * frictionConstant;       // The Friction Force Is Added To The force
																	  // With This Addition We Obtain The Net Force Of The Spring
		mass1->applyForce(force);                    // Force Is Applied To mass1
		mass2->applyForce(-force);                   // The Opposite Of Force Is Applied To mass2
	}                                   // Void Solve() Ends Here
};

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

		for (int a = 0; a < numOfMasses - 1; ++a)                // To Create Everyone Of Each Start A Loop
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