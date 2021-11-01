// SPDX-License-Identifier: GPL-2.0
//
// Audio Mute LED trigger
//

#include <linux/kernel.h>
#include <linux/leds.h>
#include <linux/module.h>
<<<<<<< HEAD
#include "../leds.h"

static enum led_brightness audio_state[NUM_AUDIO_LEDS];

static int ledtrig_audio_mute_activate(struct led_classdev *led_cdev)
{
	led_set_brightness_nosleep(led_cdev, audio_state[LED_AUDIO_MUTE]);
	return 0;
}

static int ledtrig_audio_micmute_activate(struct led_classdev *led_cdev)
{
	led_set_brightness_nosleep(led_cdev, audio_state[LED_AUDIO_MICMUTE]);
	return 0;
}

static struct led_trigger ledtrig_audio[NUM_AUDIO_LEDS] = {
	[LED_AUDIO_MUTE] = {
		.name     = "audio-mute",
		.activate = ledtrig_audio_mute_activate,
	},
	[LED_AUDIO_MICMUTE] = {
		.name     = "audio-micmute",
		.activate = ledtrig_audio_micmute_activate,
	},
};

=======

static struct led_trigger *ledtrig_audio[NUM_AUDIO_LEDS];
static enum led_brightness audio_state[NUM_AUDIO_LEDS];

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
enum led_brightness ledtrig_audio_get(enum led_audio type)
{
	return audio_state[type];
}
EXPORT_SYMBOL_GPL(ledtrig_audio_get);

void ledtrig_audio_set(enum led_audio type, enum led_brightness state)
{
	audio_state[type] = state;
<<<<<<< HEAD
	led_trigger_event(&ledtrig_audio[type], state);
=======
	led_trigger_event(ledtrig_audio[type], state);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
EXPORT_SYMBOL_GPL(ledtrig_audio_set);

static int __init ledtrig_audio_init(void)
{
<<<<<<< HEAD
	led_trigger_register(&ledtrig_audio[LED_AUDIO_MUTE]);
	led_trigger_register(&ledtrig_audio[LED_AUDIO_MICMUTE]);
=======
	led_trigger_register_simple("audio-mute",
				    &ledtrig_audio[LED_AUDIO_MUTE]);
	led_trigger_register_simple("audio-micmute",
				    &ledtrig_audio[LED_AUDIO_MICMUTE]);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	return 0;
}
module_init(ledtrig_audio_init);

static void __exit ledtrig_audio_exit(void)
{
<<<<<<< HEAD
	led_trigger_unregister(&ledtrig_audio[LED_AUDIO_MUTE]);
	led_trigger_unregister(&ledtrig_audio[LED_AUDIO_MICMUTE]);
=======
	led_trigger_unregister_simple(ledtrig_audio[LED_AUDIO_MUTE]);
	led_trigger_unregister_simple(ledtrig_audio[LED_AUDIO_MICMUTE]);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
module_exit(ledtrig_audio_exit);

MODULE_DESCRIPTION("LED trigger for audio mute control");
MODULE_LICENSE("GPL v2");
