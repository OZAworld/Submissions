using UnityEngine;
using System.Collections;

public class goGameMain : MonoBehaviour {

	GameObject start;
	bool gameFlag;

	// Use this for initialization
	void Start () {
		start = GameObject.Find ("ice_2");
	}
	
	// Update is called once per frame
	void Update () {
	
	if (Input.GetMouseButtonDown (0)) 
	{

		Ray ray = new Ray ();
		RaycastHit hit = new RaycastHit ();
		ray = Camera.main.ScreenPointToRay (Input.mousePosition);


		if (Physics.Raycast (ray.origin, ray.direction, out hit, Mathf.Infinity)) {
			if (hit.collider.gameObject == start) 
			{
					gameFlag = true;				
			}

		}

			if (gameFlag == true) 
		{
		
			Application.LoadLevel ("TestScene");
		}
	}
}
}