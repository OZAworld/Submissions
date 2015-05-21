using UnityEngine;
using System.Collections;

public class penpenMove : MonoBehaviour {

	public CreatePrefabScript CPS;
	public GameObject CPSobject;
	public GameObject Ice;

	penpenDeath PenDeath;

	public GameObject fade;
	SpriteRenderer fadeOUT;
	public float alpha;

	public GameObject Pen;
	public GameObject Killer;

	public GameObject checkArea;
	private Vector3 acceleration;

	float penMove_x;
	float penMove_y;
	float penMoveSpeed;

	Vector3 m_pos;
	bool moveStart;

	public bool hits;
	public bool hitFlag1;
	public bool hitFlag2;
	public bool hitFlag3;
	bool deathFlag;
	public bool clearFlag;
	bool startFlag;


	float startTime;
	public float Timer;
	float deathTimer;

	// Use this for initialization
	void Start () {
		CPSobject = GameObject.Find ("GameObject");
		CPS = CPSobject.GetComponent<CreatePrefabScript>();

		PenDeath = GetComponent<penpenDeath> ();

		fade = GameObject.Find ("fadeOut");
		fadeOUT = fade.GetComponent<SpriteRenderer> ();
		alpha = 0.0f;

		penMove_x = 0.5f;
		penMove_y = 0.005f;
		penMoveSpeed = 0.1f;
		moveStart = false;
		clearFlag = false;
		startFlag = false;
		hitFlag1 = false;

		deathTimer = 0;
		Timer = 0;

		m_pos = transform.localPosition;
	}
	
	// Update is called once per frame
	void Update () {
		Ice = GameObject.Find ("iceBlock" + (CPS.number - 1).ToString());
		Pen = GameObject.Find ("penpen");
		this.acceleration = Input.acceleration;

		fadeOUT.color = new Color (1, 1, 1, alpha);

		RaycastHit hit = new RaycastHit ();



		Debug.DrawRay (transform.position, Vector3.down, Color.red, 10.0f, true);
		if (Physics.Raycast (transform.position, Vector3.down, out hit, 0.5f)) 
		{
			if (hit.collider.gameObject.name != "penpen") 
			{
				Debug.Log (hit.collider.gameObject.name);
				hits = true;
				Timer = 0;
			}
			if (hit.collider.gameObject.name == "penpen" && hitFlag2 == false && clearFlag == false) 
			{
				Timer += Time.deltaTime;
				if (Timer >= 1.3f) 
				{
					deathFlag = true;
				}
			}
		}


		if (startTime < 1.0f) 
		{
			startTime += Time.deltaTime;
		}
		if (startTime >= 1.0f) 
		{
			startTime = 1.0f;
			moveStart = true;
		}
		if (moveStart == true) 
		{
			Destroy (checkArea);
			m_pos.y -= penMove_y;
			if (System.Math.Round(this.acceleration.y, 3) <= -0.2f) 
			{
				m_pos.y -= penMove_y;
			}
			m_pos.x += penMove_x * (float)System.Math.Round(this.acceleration.x, 3) * penMoveSpeed * 2;

			transform.localPosition = m_pos;
		}




		if (hitFlag1 == false && hitFlag2 == false && hits == false) 
		{
			//deathFlag = true;
		}

		if (deathFlag == true && clearFlag == false) 
		{
			penpenDeath ();
		}

		if (clearFlag == true) 
		{
			alpha += 0.01f;
			if (alpha >= 1) 
			{
				penMove_y = 0;
				Application.LoadLevel ("clear");
			}
		}
	}


	void OnTriggerEnter (Collider collider)
	{
		if (collider.gameObject == Ice) 
		{
			hitFlag1 = true;
		}

		if (collider.gameObject.name == "riku_ice") 
		{
			hitFlag2 = true;
		}

		if (collider.gameObject.name == ("iceBlock" + (CPS.number - 2).ToString ())) 
		{
			hits = true;
		}

		if (collider.gameObject.name == "riku_mama") 
		{

			clearFlag = true;

		}
	}
/*
	void OnTriggerStay (Collider collider)
	{
		//hit = true;
		//hitFlag1 = true;
		hitFlag3 = true;
		if (collider.gameObject.name == ("iceBlock" + (CPS.number - 2).ToString ()) || collider.gameObject == Ice) 
		{
			hits = true;
		}
	}
*/
	void OnTriggerExit (Collider collider)
	{
		//hitFlag3 = false;
		/*
		if (collider.gameObject.name == ("iceBlock" + (CPS.number - 2).ToString ())) 
		{
			hitFlag1 = false;
			hits = false;
		}

		if (collider.gameObject == Ice) 
		{
			hitFlag3 = false;
		}
*/
		if (collider.gameObject.name == "riku_ice") 
		{
			hitFlag2 = false;
		}


	}

	void penpenDeath()
	{
		penMove_y = 0;
		penMove_x = 0;

		audio.Stop ();

		Destroy (Pen);
		PenDeath.oboPen_create ();
	}
}
