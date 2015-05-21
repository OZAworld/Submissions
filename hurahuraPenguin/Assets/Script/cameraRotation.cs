using UnityEngine;
using System.Collections;

public class cameraRotation : MonoBehaviour {

	public GameObject Pen;

	// Use this for initialization
	void Start () {
		Pen = GameObject.Find ("penpen");
	}
	
	// Update is called once per frame
	void Update () {
		transform.rotation = Quaternion.Euler (new Vector3 (0, 0, 0));
		transform.position = new Vector3 (0, Pen.transform.position.y - 3.0f, -10.0f);
	}
}
