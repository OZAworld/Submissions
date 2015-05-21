using UnityEngine;
using System.Collections;

public class startButton : MonoBehaviour {

	GameObject start;
	GameObject backButton;

	bool startFlag;
	bool backFlag;



	// Use this for initialization
	void Start () {
		start = GameObject.Find ("start");

	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown (0)) 
		{

			Ray ray = new Ray();
			RaycastHit hit = new RaycastHit();
			ray = Camera.main.ScreenPointToRay(Input.mousePosition);


			if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity))
			{
				Debug.Log(hit.collider.gameObject.name);

				if (hit.collider.gameObject == start)
				{
					startFlag = true;	

				}

			}

			if (startFlag == true) 
			{
				audio.Play ();
				Application.LoadLevel ("story");
			}
		}
	}
}
