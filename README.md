# 🖥️ Operating Systems Lab Works — ISU 2025

[![Arch Linux](https://img.shields.io/badge/Linux-Arch-blue?logo=arch-linux&logoColor=white)](https://archlinux.org/)
[![Gentoo](https://img.shields.io/badge/Linux-Gentoo-purple?logo=gentoo&logoColor=white)](https://www.gentoo.org/)
[![SSH Enabled](https://img.shields.io/badge/SSH-enabled-green?logo=openssh&logoColor=white)](#)

> 💡 This repository contains lab work for the course **“Operating Systems”** at ISU in 2025.

---

## 📚 Table of Contents

- [📘 Lab Work №2: Installing Linux](#-lab-work-2-installing-linux)
  - [🛠️ Installation Process](#️installation-process)
  - [🌀 Going Further](#-going-further)
  - [🔐 SSH Setup](#-ssh-setup)
  - [🌐 Router Configuration](#-router-configuration)
  - [✅ Summary](#-summary)

---

## 📘 Lab Work №2: Installing Linux

I decided it would be more engaging to install a new Linux distribution on my personal laptop rather than inside a virtual machine (it was previously running Ubuntu). Installation was done via a bootable USB flash drive.

---

### 🛠️ Installation Process

Using the resources from the [Arch Wiki (EN)](https://wiki.archlinux.org/) and [Arch Wiki (RU)](https://wiki.archlinux.org/title/Main_page_(Русский)), and with guidance from a colleague, I successfully installed **Arch Linux**.

> 📹 **Installation video**:  
> [![Watch on YouTube](https://img.shields.io/badge/Watch%20Video-%F0%9F%93%BA-red?logo=youtube&logoColor=white)](https://youtu.be/i5FqydpN3-E)

To solidify my understanding, I repeated the installation process **two more times**.

---

### 🌀 Going Further

Later, I attempted to install **Gentoo Linux**.  
As of now, the process is ongoing — Gentoo requires a significantly deeper level of configuration and understanding.

---

### 🔐 SSH Setup

After successfully installing Arch, I configured the **SSHD server** to enable remote access via SSH.

> 📹 **SSHD configuration video**:  
> [![Watch on YouTube](https://img.shields.io/badge/Watch%20Video-%F0%9F%93%BA-red?logo=youtube&logoColor=white)](https://youtu.be/S8vru6sC-OA)

---

### 🌐 Router Configuration

I began setting up **port forwarding** on my home router to allow external SSH access.

<details>
<summary>📋 Router Configuration Story</summary>

- I didn’t have access to the router's admin interface initially.
- Contacted **Rostelecom** support — a technician tried to forward ports remotely, but failed.
- Eventually received admin credentials and set everything up manually.
- Despite correct configuration, my colleague still saw the error:  
  ❌ `"Connection refused"`

> 📹 **Router troubleshooting video**:  
> [![Watch on YouTube](https://img.shields.io/badge/Watch%20Video-%F0%9F%93%BA-red?logo=youtube&logoColor=white)](https://youtu.be/J5QIRlPyFA4)

</details>

---

## ✅ Summary

| Task                            | Status    |
|---------------------------------|-----------|
| Arch Linux installation         | ✅ Done (3×) |
| SSHD server configuration       | ✅ Done     |
| Router port forwarding          | ⚠️ Partially done |
| Gentoo installation             | 🔄 In Progress |

---

## 📎 Additional Notes

- All installation steps were done without a graphical installer.
- Arch Linux was installed using manual partitioning, base system setup, and post-install configurations.
- SSH access setup included creating a user, enabling the `sshd` service, and setting up firewall rules (if any).

---

