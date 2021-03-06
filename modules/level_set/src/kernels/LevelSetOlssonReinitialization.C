//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// MOOSE includes
#include "LevelSetOlssonReinitialization.h"

registerMooseObject("LevelSetApp", LevelSetOlssonReinitialization);

template <>
InputParameters
validParams<LevelSetOlssonReinitialization>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("The re-initialization equation defined by Olsson et. al. (2007).");
  params.addRequiredCoupledVar(
      "phi_0", "The level set variable to be reinitialized as signed distance function.");
  params.addRequiredParam<PostprocessorName>(
      "epsilon", "The epsilon coefficient to be used in the reinitialization calculation.");
  return params;
}

LevelSetOlssonReinitialization::LevelSetOlssonReinitialization(const InputParameters & parameters)
  : Kernel(parameters),
    _grad_levelset_0(coupledGradient("phi_0")),
    _epsilon(getPostprocessorValue("epsilon"))
{
}

Real
LevelSetOlssonReinitialization::computeQpResidual()
{
  _s = _grad_levelset_0[_qp].norm() + std::numeric_limits<Real>::epsilon();
  _n_hat = _grad_levelset_0[_qp] / _s;
  _f = _u[_qp] * (1 - _u[_qp]) * _n_hat;
  return _grad_test[_i][_qp] * (-_f + _epsilon * (_grad_u[_qp] * _n_hat) * _n_hat);
}

Real
LevelSetOlssonReinitialization::computeQpJacobian()
{
  _s = _grad_levelset_0[_qp].norm() + std::numeric_limits<Real>::epsilon();
  _n_hat = _grad_levelset_0[_qp] / _s;
  return _grad_test[_i][_qp] * _n_hat *
         ((2 * _u[_qp] - 1) * _phi[_j][_qp] + _epsilon * (_grad_phi[_j][_qp] * _n_hat));
}
