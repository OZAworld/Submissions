using UnityEngine;
using System.Collections;

public class Killer : MonoBehaviour {

	GameObject oboPen;
	public GameObject Dead;


	void oboPen_destroy()
	{
		oboPen = GameObject.Find ("obopen(Clone)");
		Destroy (oboPen);
	}


	void OnAnimationFinish()
	{
		Instantiate (Dead, transform.position, transform.rotation);
	}

}
