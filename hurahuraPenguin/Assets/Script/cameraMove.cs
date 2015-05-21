using UnityEngine;
using System.Collections;

public class cameraMove : MonoBehaviour {

	public Vector3 m_pos;
	GameObject Next;
	GameObject Skip;


	// Use this for initialization
	void Start () {
		m_pos = transform.localPosition;
		Next = GameObject.Find ("next");
		Skip = GameObject.Find ("skip");
	}
	
	// Update is called once per frame
	void Update () {

		if (Input.GetMouseButtonDown (0)) 
		{
			Ray ray = new Ray ();
			RaycastHit hit = new RaycastHit ();
			ray = Camera.main.ScreenPointToRay (Input.mousePosition);


			if (Physics.Raycast (ray.origin, ray.direction, out hit, Mathf.Infinity)) 
			{
				Debug.Log (hit.collider.gameObject.name);

				if (hit.collider.gameObject == Next) 
				{
					m_pos.y -= 15.0f;
					transform.localPosition = m_pos;
				}
				if (m_pos.y < -75.0f) 
				{
					Application.LoadLevel ("TestScene");
				}

				if (hit.collider.gameObject == Skip)
				{
					Application.LoadLevel ("TestScene");
				}
			}
		}
	}
}
