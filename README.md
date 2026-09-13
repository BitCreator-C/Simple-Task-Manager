This application is designed to be cross-platform, supporting both **macOS** and **Linux**.

**Recommended Systems for Best Accuracy:**
*   **macOS:** Optimized for **Apple M1, M2, and earlier** chips. (Note: On newer M4 chips, CPU readings may be unstable due to architectural differences in CPU tick counting).
*   **Linux:** Full support via `/proc/stat` and `/proc/meminfo`.

If you are using a Mac M4, you might notice some fluctuations in CPU usage percentages. This is a known behavior related to the high-frequency sampling of the latest Apple Silicon.
