This is a log from a fix of sentry when it stopped working, probably due to pulling/resetting with diversion.

Activity found that sentry version on diversion was not functional on my Windows device. Solution was to reunpack the previously downloaded zip. 

Importance; Diversion does not appear to keep sentry functional. Needs further investigation. Keeping log for resolution.

## Log
Reset sentry plugin status (previously deleted) via diversion
Enabled sentry plugin, spots in files (RoveSoSimulatorInstance) (GameInstance?)
error: something something can't open/find file, and warning(?) that it was using an outdated/ineffective method to search for files (sentry specific)

attempt: Regenerate VS files
failed, same error

attempt: reunpacking sentry (via zip. if successful, diversion doesn't work for this)
compiling
success!

