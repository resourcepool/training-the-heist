import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs/index';
import { Employee } from '../../../../server/src/_interface/employee.model';
import { TnsaEmployeesService } from './tnsa-employees.service';

@Component({
  selector: 'app-tnsa-employees',
  templateUrl: './tnsa-employees.component.html',
  styleUrls: ['./tnsa-employees.component.scss'],
  providers: [TnsaEmployeesService],
})
export class TnsaEmployeesComponent implements OnInit {

  constructor(private readonly employeesService: TnsaEmployeesService,) {
  }

  STATUS = StatusEnum;
  ACCESSLEVEL = AccessLevelEnum;
  employees: Observable<Employee[]>;

  ngOnInit() {
    this.employees = this.employeesService.getEmployees();
  }
}

enum StatusEnum {
  'SECRET',
  'IN MISSION',
  'FREE',
  'RETIRED',
  'DICEASED',
}

enum AccessLevelEnum {
  '',
  'PUBLIC',
  'TNSA EMPLOYEES',
  'TNSA AGENTS',
  'CONFIDENTIAL',
  'SECRET',
  'TOP SECRET',
}
