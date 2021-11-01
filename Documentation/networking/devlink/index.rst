Linux Devlink Documentation
===========================

devlink is an API to expose device information and resources not directly
related to any device class, such as chip-wide/switch-ASIC-wide configuration.

Interface documentation
-----------------------

The following pages describe various interfaces available through devlink in
general.

.. toctree::
   :maxdepth: 1

   devlink-dpipe
   devlink-health
   devlink-info
   devlink-flash
   devlink-params
   devlink-port
   devlink-region
   devlink-resource
   devlink-reload
   devlink-trap

Driver-specific documentation
-----------------------------

Each driver that implements ``devlink`` is expected to document what
parameters, info versions, and other features it supports.

.. toctree::
   :maxdepth: 1

   bnxt
<<<<<<< HEAD
<<<<<<< HEAD
   hns3
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
   hns3
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
   ionic
   ice
   mlx4
   mlx5
   mlxsw
   mv88e6xxx
   netdevsim
   nfp
<<<<<<< HEAD
<<<<<<< HEAD
=======
   sja1105
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
   qed
   ti-cpsw-switch
   am65-nuss-cpsw-switch
   prestera
