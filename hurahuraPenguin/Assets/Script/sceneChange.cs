using UnityEngine;
using System.Collections;

public class sceneChange : MonoBehaviour {

	GameObject killer;
	GameObject backButton;

	bool backFlag;

	// Use this for initialization
	void Start () {
		killer = GameObject.Find ("killer(Clone)");
		backButton = GameObject.Find ("back");
	}
	
	// Update is called once per frame
	void Update () {
	
		Destroy (killer);

		if (Input.GetMouseButtonDown (0)) {

			Ray ray = new Ray ();
			RaycastHit hit = new RaycastHit ();
			ray = Camera.main.ScreenPointToRay (Input.mousePosition);


			if (Physics.Raycast (ray.origin, ray.direction, out hit, Mathf.Infinity)) {
				if (hit.collider.gameObject == backButton) {
					backFlag = true;			
				}

			}

			if (backFlag == true) {
				Application.LoadLevel ("title");
			}
		}
	}
}