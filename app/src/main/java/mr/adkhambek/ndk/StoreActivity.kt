package mr.adkhambek.ndk

import android.app.Activity
import android.os.Bundle
import mr.adkhambek.ndk.databinding.ActivityStoreBinding


class StoreActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding = ActivityStoreBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val store = Store()

        binding.intTextView.text = store.intFromJNI().toString()
        binding.stringTextView.text = store.stringFromJNI()

        binding.calculatedTextView.text = store.calculateFromJNI(5, 7).toString()
        binding.objectTextView.text = store.objectFromJNI().name
    }
}

class Store {
    companion object {
        init {
            System.loadLibrary("store-lib")
        }
    }

    external fun intFromJNI(): Int
    external fun stringFromJNI(): String
    external fun calculateFromJNI(a: Int, b: Int): Int
    external fun objectFromJNI(): User
}

class User(val name: String)