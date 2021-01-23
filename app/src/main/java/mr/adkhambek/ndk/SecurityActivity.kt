package mr.adkhambek.ndk

import android.app.Activity
import android.os.Bundle
import mr.adkhambek.ndk.databinding.ActivitySecurityBinding

class SecurityActivity : Activity() {

    private external fun encrypt(plainText: String): String
    private external fun decrypt(ciphertext: String): String

    companion object {
        init {
            System.loadLibrary("security-lib")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding = ActivitySecurityBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val encoded = encrypt(getString(R.string.app_name))
        val decoded = decrypt(encoded)

        binding.encodeText.text = encoded
        binding.decodeText.text = decoded
    }
}