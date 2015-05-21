using UnityEngine;
using System.Collections;

public class goBackTitle : MonoBehaviour {

	GameObject backButton;
	bool backFlag;

	// Use this for initialization
	void Start () {
		backButton = GameObject.Find ("back");
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown (0)) 
		{

			Ray ray = new Ray ();
			RaycastHit hit = new RaycastHit ();
			ray = Camera.main.ScreenPointToRay (Input.mousePosition);


			if (Physics.Raycast (ray.origin, ray.direction, out hit, Mathf.Infinity)) {
				if (hit.collider.gameObject == backButton) 
				{
					backFlag = true;
					audio.Play ();
				}

			}

			if (backFlag == true) 
			{

				Application.LoadLevel ("title");
			}
		}
	}
}
