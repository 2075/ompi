! -*- fortran -*-
!
! Copyright (c) 2004-2006 The Trustees of Indiana University and Indiana
!                         University Research and Technology
!                         Corporation.  All rights reserved.
! Copyright (c) 2004-2010 The University of Tennessee and The University
!                         of Tennessee Research Foundation.  All rights
!                         reserved.
! Copyright (c) 2004-2007 High Performance Computing Center Stuttgart,
!                         University of Stuttgart.  All rights reserved.
! Copyright (c) 2004-2005 The Regents of the University of California.
!                         All rights reserved.
! Copyright (c) 2006-2012 Cisco Systems, Inc.  All rights reserved.
! Copyright (c) 2009      Oak Ridge National Labs.  All rights reserved.
! $COPYRIGHT$
!
! Additional copyrights may follow
!
! $HEADER$
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! Do ***not*** copy this file to the directory where your Fortran
! fortran application is compiled unless it is absolutely necessary!  Most
! modern Fortran compilers now support the -I command line flag, which
! tells the compiler where to find .h files (specifically, this one).  For
! example:
!
!      shell$ mpif77 foo.f -o foo -I$OMPI_HOME/include
!
! will probably do the trick (assuming that you have set OMPI_HOME
! properly).
!
! That being said, OMPI's "mpif77" wrapper compiler should
! automatically include the -I option for you.  The following command
! should be equivalent to the command listed above:
!
!      shell$ mpif77 foo.f -o foo
!
! You should not copy this file to your local directory because it is
! possible that this file will be changed between versions of Open MPI.
! Indeed, this mpif.h is incompatible with the mpif.f of other
! implementations of MPI.  Using this mpif.h with other implementations
! of MPI, or with other versions of Open MPI will result in undefined
! behavior (to include incorrect results, segmentation faults,
! unexplainable "hanging" in your application, etc.).  Always use the
! -I command line option instead (or let mpif77 do it for you).
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

!
!     This file contains the bulk of the Open MPI Fortran interface.  It
!     is included as a back-end file to both mpif.h (i.e., the
!     standardized MPI Fortran header file) and mpi.f90 (the MPI-2
!     Fortran module source file, found in ompi/mpi/f90).
!
!     This file is marginally different than mpif.h.  mpif.h includes
!     some "external" statements that are not suitable for use with the
!     MPI-2 F90 module, and therefore cannot be included in the mpi.f90
!     source file.  Hence, this file is essentially everything that
!     needs to be in the standardized mpif.h *except* the "external"
!     statements, and is therefore suitable to be included in mpi.f90.
!

!
!     First, however, include some output from configure.
!
      include 'mpif-config.h'

!
!     MPI version
!
      integer MPI_VERSION, MPI_SUBVERSION

      parameter (MPI_VERSION=2)
      parameter (MPI_SUBVERSION=1)
!
!     Miscellaneous constants
!
      integer MPI_ANY_SOURCE, MPI_ANY_TAG
      integer MPI_PROC_NULL
      integer MPI_ROOT
      integer MPI_UNDEFINED
      integer MPI_CART, MPI_GRAPH, MPI_KEYVAL_INVALID
      integer MPI_SOURCE, MPI_TAG, MPI_ERROR
      integer MPI_TAG_UB, MPI_HOST, MPI_IO, MPI_WTIME_IS_GLOBAL
      integer MPI_APPNUM, MPI_LASTUSEDCODE, MPI_UNIVERSE_SIZE
      integer IMPI_CLIENT_SIZE, IMPI_CLIENT_COLOR
      integer IMPI_HOST_SIZE, IMPI_HOST_COLOR
      integer MPI_BSEND_OVERHEAD
      integer MPI_ORDER_C, MPI_ORDER_FORTRAN
      integer MPI_DISTRIBUTE_BLOCK, MPI_DISTRIBUTE_CYCLIC
      integer MPI_DISTRIBUTE_NONE, MPI_DISTRIBUTE_DFLT_DARG
      integer MPI_TYPECLASS_INTEGER, MPI_TYPECLASS_REAL
      integer MPI_TYPECLASS_COMPLEX
      integer MPI_MODE_NOCHECK, MPI_MODE_NOPRECEDE, MPI_MODE_NOPUT
      integer MPI_MODE_NOSTORE, MPI_MODE_NOSUCCEED
      integer MPI_LOCK_EXCLUSIVE, MPI_LOCK_SHARED
      integer MPI_WIN_BASE, MPI_WIN_SIZE, MPI_WIN_DISP_UNIT
      integer MPI_MESSAGE_NO_PROC

      parameter (MPI_ANY_SOURCE=-1)
      parameter (MPI_ANY_TAG=-1)
      parameter (MPI_PROC_NULL=-2)
      parameter (MPI_ROOT=-4)
      parameter (MPI_UNDEFINED=-32766)
      parameter (MPI_CART=1)
      parameter (MPI_GRAPH=2)
      parameter (MPI_KEYVAL_INVALID=-1)
      parameter (MPI_SOURCE=1)
      parameter (MPI_TAG=2)
      parameter (MPI_ERROR=3)
      parameter (MPI_TAG_UB=0)
      parameter (MPI_HOST=1)
      parameter (MPI_IO=2)
      parameter (MPI_WTIME_IS_GLOBAL=3)
      parameter (MPI_APPNUM=4)
      parameter (MPI_LASTUSEDCODE=5)
      parameter (MPI_UNIVERSE_SIZE=6)
      parameter (MPI_WIN_BASE=7)
      parameter (MPI_WIN_SIZE=8)
      parameter (MPI_WIN_DISP_UNIT=9)
      parameter (IMPI_CLIENT_SIZE=10)
      parameter (IMPI_CLIENT_COLOR=11)
      parameter (IMPI_HOST_SIZE=12)
      parameter (IMPI_HOST_COLOR=13)

      parameter (MPI_BSEND_OVERHEAD=128)
      parameter (MPI_ORDER_C=0)
      parameter (MPI_ORDER_FORTRAN=1)
      parameter (MPI_DISTRIBUTE_BLOCK=0)
      parameter (MPI_DISTRIBUTE_CYCLIC=1)
      parameter (MPI_DISTRIBUTE_NONE=2)
      parameter (MPI_DISTRIBUTE_DFLT_DARG=-1)
      parameter (MPI_TYPECLASS_INTEGER=1)
      parameter (MPI_TYPECLASS_REAL=2)
      parameter (MPI_TYPECLASS_COMPLEX=3)
      parameter (MPI_MODE_NOCHECK=1)
      parameter (MPI_MODE_NOPRECEDE=2)
      parameter (MPI_MODE_NOPUT=4)
      parameter (MPI_MODE_NOSTORE=8)
      parameter (MPI_MODE_NOSUCCEED=16)
      parameter (MPI_LOCK_EXCLUSIVE=1)
      parameter (MPI_LOCK_SHARED=2)
      parameter (MPI_MESSAGE_NO_PROC=1)

!
!     MPI_Init_thread constants
!
      integer MPI_THREAD_SINGLE, MPI_THREAD_FUNNELED
      integer MPI_THREAD_SERIALIZED, MPI_THREAD_MULTIPLE

      parameter (MPI_THREAD_SINGLE=0)
      parameter (MPI_THREAD_FUNNELED=1)
      parameter (MPI_THREAD_SERIALIZED=2)
      parameter (MPI_THREAD_MULTIPLE=3)
!
!     error classes
!
      integer MPI_SUCCESS
      integer MPI_ERR_BUFFER
      integer MPI_ERR_COUNT
      integer MPI_ERR_TYPE
      integer MPI_ERR_TAG
      integer MPI_ERR_COMM
      integer MPI_ERR_RANK
      integer MPI_ERR_REQUEST
      integer MPI_ERR_ROOT
      integer MPI_ERR_GROUP
      integer MPI_ERR_OP
      integer MPI_ERR_TOPOLOGY
      integer MPI_ERR_DIMS
      integer MPI_ERR_ARG
      integer MPI_ERR_UNKNOWN
      integer MPI_ERR_TRUNCATE
      integer MPI_ERR_OTHER
      integer MPI_ERR_INTERN
      integer MPI_ERR_IN_STATUS
      integer MPI_ERR_PENDING
      integer MPI_ERR_ACCESS
      integer MPI_ERR_AMODE
      integer MPI_ERR_ASSERT
      integer MPI_ERR_BAD_FILE
      integer MPI_ERR_BASE
      integer MPI_ERR_CONVERSION
      integer MPI_ERR_DISP
      integer MPI_ERR_DUP_DATAREP
      integer MPI_ERR_FILE_EXISTS
      integer MPI_ERR_FILE_IN_USE
      integer MPI_ERR_FILE
      integer MPI_ERR_INFO_KEY
      integer MPI_ERR_INFO_NOKEY
      integer MPI_ERR_INFO_VALUE
      integer MPI_ERR_INFO
      integer MPI_ERR_IO
      integer MPI_ERR_KEYVAL
      integer MPI_ERR_LOCKTYPE
      integer MPI_ERR_NAME
      integer MPI_ERR_NO_MEM
      integer MPI_ERR_NOT_SAME
      integer MPI_ERR_NO_SPACE
      integer MPI_ERR_NO_SUCH_FILE
      integer MPI_ERR_PORT
      integer MPI_ERR_QUOTA
      integer MPI_ERR_READ_ONLY
      integer MPI_ERR_RMA_CONFLICT
      integer MPI_ERR_RMA_SYNC
      integer MPI_ERR_SERVICE
      integer MPI_ERR_SIZE
      integer MPI_ERR_SPAWN
      integer MPI_ERR_UNSUPPORTED_DATAREP
      integer MPI_ERR_UNSUPPORTED_OPERATION
      integer MPI_ERR_WIN

      integer MPI_ERR_SYSRESOURCE
      integer MPI_ERR_LASTCODE

      parameter( MPI_SUCCESS                  = 0)
      parameter( MPI_ERR_BUFFER               = 1)
      parameter( MPI_ERR_COUNT                = 2)
      parameter( MPI_ERR_TYPE                 = 3)
      parameter( MPI_ERR_TAG                  = 4)
      parameter( MPI_ERR_COMM                 = 5)
      parameter( MPI_ERR_RANK                 = 6)
      parameter( MPI_ERR_REQUEST              = 7)
      parameter( MPI_ERR_ROOT                 = 8)
      parameter( MPI_ERR_GROUP                = 9)
      parameter( MPI_ERR_OP                   = 10)
      parameter( MPI_ERR_TOPOLOGY             = 11)
      parameter( MPI_ERR_DIMS                 = 12)
      parameter( MPI_ERR_ARG                  = 13)
      parameter( MPI_ERR_UNKNOWN              = 14)
      parameter( MPI_ERR_TRUNCATE             = 15)
      parameter( MPI_ERR_OTHER                = 16)
      parameter( MPI_ERR_INTERN               = 17)
      parameter( MPI_ERR_IN_STATUS            = 18)
      parameter( MPI_ERR_PENDING              = 19)
      parameter( MPI_ERR_ACCESS               = 20)
      parameter( MPI_ERR_AMODE                = 21)
      parameter( MPI_ERR_ASSERT               = 22)
      parameter( MPI_ERR_BAD_FILE             = 23)
      parameter( MPI_ERR_BASE                 = 24)
      parameter( MPI_ERR_CONVERSION           = 25)
      parameter( MPI_ERR_DISP                 = 26)
      parameter( MPI_ERR_DUP_DATAREP          = 27)
      parameter( MPI_ERR_FILE_EXISTS          = 28)
      parameter( MPI_ERR_FILE_IN_USE          = 29)
      parameter( MPI_ERR_FILE                 = 30)
      parameter( MPI_ERR_INFO_KEY             = 31)
      parameter( MPI_ERR_INFO_NOKEY           = 32)
      parameter( MPI_ERR_INFO_VALUE           = 33)
      parameter( MPI_ERR_INFO                 = 34)
      parameter( MPI_ERR_IO                   = 35)
      parameter( MPI_ERR_KEYVAL               = 36)
      parameter( MPI_ERR_LOCKTYPE             = 37)
      parameter( MPI_ERR_NAME                 = 38)
      parameter( MPI_ERR_NO_MEM               = 39)
      parameter( MPI_ERR_NOT_SAME             = 40)
      parameter( MPI_ERR_NO_SPACE             = 41)
      parameter( MPI_ERR_NO_SUCH_FILE         = 42)
      parameter( MPI_ERR_PORT                 = 43)
      parameter( MPI_ERR_QUOTA                = 44)
      parameter( MPI_ERR_READ_ONLY            = 45)
      parameter( MPI_ERR_RMA_CONFLICT         = 46)
      parameter( MPI_ERR_RMA_SYNC             = 47)
      parameter( MPI_ERR_SERVICE              = 48)
      parameter( MPI_ERR_SIZE                 = 49)
      parameter( MPI_ERR_SPAWN                = 50)
      parameter( MPI_ERR_UNSUPPORTED_DATAREP  = 51)
      parameter( MPI_ERR_UNSUPPORTED_OPERATION= 52)
      parameter( MPI_ERR_WIN                  = 53)

      parameter( MPI_ERR_SYSRESOURCE          = -2)
      parameter( MPI_ERR_LASTCODE             = 54)

!
!     comparison results
!
      integer MPI_IDENT, MPI_CONGRUENT, MPI_SIMILAR, MPI_UNEQUAL

      parameter (MPI_IDENT=0)
      parameter (MPI_CONGRUENT=1)
      parameter (MPI_SIMILAR=2)
      parameter (MPI_UNEQUAL=3)
!
!     datatype combiners
!
      integer MPI_COMBINER_NAMED
      integer MPI_COMBINER_DUP
      integer MPI_COMBINER_CONTIGUOUS
      integer MPI_COMBINER_VECTOR
      integer MPI_COMBINER_HVECTOR_INTEGER
      integer MPI_COMBINER_HVECTOR
      integer MPI_COMBINER_INDEXED
      integer MPI_COMBINER_HINDEXED_INTEGER
      integer MPI_COMBINER_HINDEXED
      integer MPI_COMBINER_INDEXED_BLOCK
      integer MPI_COMBINER_STRUCT_INTEGER
      integer MPI_COMBINER_STRUCT
      integer MPI_COMBINER_SUBARRAY
      integer MPI_COMBINER_DARRAY
      integer MPI_COMBINER_F90_REAL
      integer MPI_COMBINER_F90_COMPLEX
      integer MPI_COMBINER_F90_INTEGER
      integer MPI_COMBINER_RESIZED
      integer MPI_COMBINER_HINDEXED_BLOCK

      parameter (MPI_COMBINER_NAMED=0)
      parameter (MPI_COMBINER_DUP=1)
      parameter (MPI_COMBINER_CONTIGUOUS=2)
      parameter (MPI_COMBINER_VECTOR=3)
      parameter (MPI_COMBINER_HVECTOR_INTEGER=4)
      parameter (MPI_COMBINER_HVECTOR=5)
      parameter (MPI_COMBINER_INDEXED=6)
      parameter (MPI_COMBINER_HINDEXED_INTEGER=7)
      parameter (MPI_COMBINER_HINDEXED=8)
      parameter (MPI_COMBINER_INDEXED_BLOCK=9)
      parameter (MPI_COMBINER_STRUCT_INTEGER=10)
      parameter (MPI_COMBINER_STRUCT=11)
      parameter (MPI_COMBINER_SUBARRAY=12)
      parameter (MPI_COMBINER_DARRAY=13)
      parameter (MPI_COMBINER_F90_REAL=14)
      parameter (MPI_COMBINER_F90_COMPLEX=15)
      parameter (MPI_COMBINER_F90_INTEGER=16)
      parameter (MPI_COMBINER_RESIZED=17)
      parameter (MPI_COMBINER_HINDEXED_BLOCK=18)

! 
! Communicator split type constants.
!
      integer MPI_COMM_TYPE_SHARED
      parameter (MPI_COMM_TYPE_SHARED=0)