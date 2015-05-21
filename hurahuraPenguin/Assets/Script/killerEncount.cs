using UnityEngine;
using System.Collections;

public class killerEncount : MonoBehaviour {

	float deathTimer;
	bool killerFlag;
	penpenDeath PenDeath;

	// Use this for initialization
	void Start () {
		PenDeath = GetComponent<penpenDeath> ();
		deathTimer = 0;
		killerFlag = false;
	}
	
	// Update is called once per frame
	void Update () {
	
		if (deathTimer < 2.0f && killerFlag == false) 
		{
			deathTimer += Time.deltaTime;
			if (deathTimer >= 2.0f) 
			{
				deathTimer = 2.0f;
				killerFlag = true;
			}

		}


		if (killerFlag == true && deathTimer == 2.0f) 
		{
			deathTimer = 0;
			PenDeath.killer_create ();
		}

	}
}
